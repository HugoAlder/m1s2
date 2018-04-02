package com.lightbend.akka.sample;

import akka.actor.AbstractActor;
import akka.actor.ActorRef;
import akka.actor.ActorSystem;
import akka.actor.InvalidActorNameException;
import akka.actor.Props;
import akka.event.Logging;
import akka.event.LoggingAdapter;
import bean.MessageToAll;
import bean.MessageToSons;

public class NodeActor extends AbstractActor{

	private MyNode node;
	private ActorSystem system;
	
	private LoggingAdapter log = Logging.getLogger(getContext().getSystem(), this);
	
	public NodeActor(MyNode node, ActorSystem system) {
		this.node = node;
		this.system = system;
	}
	
	static public Props props(MyNode node, ActorSystem system) {
		return Props.create(NodeActor.class, () -> new NodeActor(node, system));
	}
	
	@Override
	public Receive createReceive() {
		return receiveBuilder()
			.match(MessageToSons.class, msg -> {
				for (MyNode n : this.node.son) {
					// If this actor is already known, we don't create it again
					ActorRef sonRef;
					try {
						sonRef = system.actorOf(NodeActor.props(n, system), n.getName());
					} catch (InvalidActorNameException e) {
						sonRef = system.actorOf(Props.create(NodeActor.class, n, system));
					}
					sonRef.tell(msg, ActorRef.noSender());
				}
				log.info(msg.message);
			})	
			.match(MessageToAll.class, msg -> {
				if (this.node.isRoot()) {
					ActorRef rootRef = system.actorOf(Props.create(NodeActor.class, this.node, system));
					rootRef.tell(new MessageToSons(msg.message), ActorRef.noSender());
				} else {
					MyNode father = this.node.father;
					ActorRef fatherRef;
					try {
						fatherRef = system.actorOf(NodeActor.props(father, system), this.node.getName());
					} catch (InvalidActorNameException e) {
						fatherRef = system.actorOf(Props.create(NodeActor.class, father, system));
					}
					fatherRef.tell(msg, ActorRef.noSender());
				}
			})
		.build();
	}
	
}
