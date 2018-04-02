package com.lightbend.akka.sample;

import java.util.ArrayList;

public class MyNode {

	protected MyNode father;
	protected ArrayList<MyNode> son;
	protected int id;
	protected String system;

	@SuppressWarnings("unchecked")
	public MyNode(MyNode father, ArrayList<MyNode> son, int id, String system) {
		this.father = father;
		this.id = id;
		this.system = system;
		if (null == son)
			this.son = new ArrayList<MyNode>();
		else
			this.son = (ArrayList<MyNode>) son.clone();
	}
	
	public void addSon(MyNode son) {
		this.son.add(son);
		son.father = this;
	}
	
	public void addSon(ArrayList<MyNode> son) {
		this.son.addAll(son);
		for (MyNode n : son) {
			n.father = this;
		}
	}
	
	public String getName() {
		if (this.id == 0)
			return "root";
		return "node" + this.id;
	}
	
	public boolean isRoot() {
		return this.id == 0;
	}

	@Override
	public String toString() {
		String res = "";
		res += getName();
		if (this.father != null)
			res += "  Father : " + father.id;
		if (this.son != null)
			res += "  Son(s) : " + son.size();
		if (system != null)
			res += "  System : " + system;
		return res;
	}
	
}
