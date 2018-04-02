package com.lightbend.akka.sample;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import org.xml.sax.SAXException;

public class Builder {

	private File inputFile;
	private DocumentBuilderFactory dbFactory;
	private DocumentBuilder dBuilder;
	private Document doc;
	
	private ArrayList<MyNode> nodes = new ArrayList<MyNode>();
	private ArrayList<String> systems =  new ArrayList<String>();

	public Builder(String filePath) throws ParserConfigurationException, SAXException, IOException {
		this.inputFile = new File(filePath);
		this.dbFactory = DocumentBuilderFactory.newInstance();
		this.dBuilder = this.dbFactory.newDocumentBuilder();
		this.doc = dBuilder.parse(inputFile);
	}

	public void build() {
		doc.getDocumentElement().normalize();
		System.out.println("Root element : " + doc.getDocumentElement().getNodeName());
		NodeList nList = doc.getElementsByTagName("system");
		
		Node nRoot = doc.getElementsByTagName("root").item(0);
		Element eRoot = (Element) nRoot;
		int rootId = Integer.parseInt(eRoot.getAttribute("id"));
		String system = eRoot.getAttribute("system");
		MyNode root = new MyNode(null, null, rootId, system);
		nodes.add(root);
		
		for (int temp = 0; temp < nList.getLength(); temp++) {
			Node nNode = nList.item(temp);

			if (nNode.getNodeType() == Node.ELEMENT_NODE) {
				Element eElement = (Element) nNode;
				system = eElement.getAttribute("name");
				systems.add(system);
				
				NodeList nodeList = eElement.getElementsByTagName("node");
				for (int j = 0; j < nodeList.getLength(); j++) {
					Node myNode = nodeList.item(j);
					
					if (myNode.getNodeType() == Node.ELEMENT_NODE) {
						Element myElement = (Element) myNode;
						int id = Integer.parseInt(myElement.getAttribute("id"));
						int fatherId = Integer.parseInt(myElement.getAttribute("father"));

						ArrayList<MyNode> cpy = (ArrayList<MyNode>) nodes.clone();
						for (MyNode n : cpy) {
							if (n.id == fatherId) {
								MyNode son = new MyNode(n, null, id, system);
								n.addSon(son);
								nodes.add(son);
							}
						}
						
					}
				}

			}
		}
	}
	
	public ArrayList<MyNode> getNodes() {
		return this.nodes;
	}
	
	public ArrayList<String> getSystem() {
		return this.systems;
	}

}
