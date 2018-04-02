package com.lightbend.akka.sample;

import java.io.IOException;
import java.util.HashMap;

import javax.xml.parsers.ParserConfigurationException;

import org.xml.sax.SAXException;

import akka.actor.ActorRef;
import akka.actor.ActorSystem;
import bean.MessageToAll;

public class Main {
	public static void main(String[] args) throws ParserConfigurationException, SAXException, IOException {
		
		Builder builder = new Builder("config.xml");
		builder.build();
		
		HashMap<String, ActorSystem> systems = new HashMap<String, ActorSystem>();
		HashMap<String, ActorRef> actors = new HashMap<String, ActorRef>();
		
		for (String s : builder.getSystem()) {
			systems.put(s, ActorSystem.create(s));
		}
		
		for (MyNode n : builder.getNodes()) {
			System.out.println(n.toString());
		}
		
		for (MyNode n : builder.getNodes()) {
			ActorSystem system;
			system = systems.get(n.system);
			actors.put(n.getName(), system.actorOf(NodeActor.props(n, system), n.getName()));
		}
		
		actors.get("root").tell(new MessageToAll("This is a really simple message"), ActorRef.noSender());

		
		try {
			// #create-actors
			/*MyNode root = new MyNode(null, null);
			MyNode node1 = new MyNode(null, null);
			MyNode node2 = new MyNode(null, null);
			MyNode node3 = new MyNode(null, null);
			MyNode node4 = new MyNode(null, null);
			MyNode node5 = new MyNode(null, null);
			
			root.addSon(node1);
			root.addSon(node4);
			node1.addSon(node2);
			node1.addSon(node3);
			node4.addSon(node5);
			node3.addSon(node5);*/
			
			//final ActorRef node1Actor = system.actorOf(NodeActor.props(node1, system), node1.getName());
			//node1Actor.tell(new MessageToAll("This is a really simple message"), ActorRef.noSender());
			
			//final ActorRef rootActor = system.actorOf(NodeActor.props(root, system), root.getName());
			//rootActor.tell(new MessageToAll("Message to all sent from root"), ActorRef.noSender());
			
			//final ActorRef rootActor = system.actorOf(NodeActor.props(root, system), root.getName());
			//rootActor.tell(new MessageToSons("Message to sons sent from root"), ActorRef.noSender());
			
			//final ActorRef nodeActor = system.actorOf(NodeActor.props(node1, system), node1.getName());
			//nodeActor.tell(new MessageToAll("Message sent from " + nodeActor.path()), ActorRef.noSender());
			
			
			/*final ActorRef printerActor = system.actorOf(Printer.props(), "printerActor");
			final ActorRef howdyGreeter = system.actorOf(Greeter.props("Howdy", printerActor), "howdyGreeter");
			final ActorRef helloGreeter = system.actorOf(Greeter.props("Hello", printerActor), "helloGreeter");
			final ActorRef goodDayGreeter = system.actorOf(Greeter.props("Good day", printerActor), "goodDayGreeter");
			// #create-actors

			// #main-send-messages
			howdyGreeter.tell(new WhoToGreet("Akka"), ActorRef.noSender());
			howdyGreeter.tell(new Greet(), ActorRef.noSender());

			howdyGreeter.tell(new WhoToGreet("Lightbend"), ActorRef.noSender());
			howdyGreeter.tell(new Greet(), ActorRef.noSender());

			helloGreeter.tell(new WhoToGreet("Java"), ActorRef.noSender());
			helloGreeter.tell(new Greet(), ActorRef.noSender());

			goodDayGreeter.tell(new WhoToGreet("Play"), ActorRef.noSender());
			goodDayGreeter.tell(new Greet(), ActorRef.noSender());
			// #main-send-messages */

			System.out.println(">>> Press ENTER to exit <<<");
			System.in.read();
		} catch (IOException ioe) {
		} finally {
			//system.terminate();
		}
	}
}
