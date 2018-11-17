#pragma once
// BehaviourTree Based in http://www.cplusplus.com/forum/general/141582/
class BehaviourTree
{
public:
	BehaviourTree();
	~BehaviourTree();

	class Node {
	public:
		virtual bool run() = 0;
	};

	class CompositeNode : public Node {
	public:
		const std::vector<Node*> GetChildren() const { return children; }
		void AddChild(Node* child) { children.push_back(child); }
		void AddChildren(std::vector<Node*> newChildren) { for (Node* child : newChildren) AddChild(child); }
	private:
		std::vector<Node*> children;
	};

	class Selector : public CompositeNode {
	public:
		virtual bool run() override {
			for (Node* child : GetChildren()) {  
				if (child->run())  
					return true;
			}
			return false;  
		}
	};

	class Sequence : public CompositeNode {
	public:
		virtual bool run() override {
			for (Node* child : GetChildren()) {  
				if (!child->run())  
					return false;
			}
			return true;  
		}
	};

	class DecoratorNode : public Node {  
	public:
		void setChild(Node* newChild) { child = newChild; }
	private:
		Node* child;  
	protected:
		Node* getChild() const { return child; }
	};

	class Root : public DecoratorNode {
	private:
		friend class BehaviourTree;
		virtual bool run() override { return getChild()->run(); }
	};

};

