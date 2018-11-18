#pragma once
// BehaviourTree Based in https://goo.gl/VkrZBH and https://goo.gl/SAVaVh

namespace LionsVersusAntilopes
{

	class Node {
	public:
		enum Status { Fail = 0, Ok = 1, Active = 2 };
		Status PresentStatus = Fail;
		virtual Status Update() = 0;
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
		virtual Status Update() override {
			for (Node* child : GetChildren()) {
				if (child->Update() == Node::Status::Active)
					return Node::Status::Active;
				else if (child->Update() == Node::Status::Ok)
					return Node::Status::Ok;
			}
			return Node::Status::Fail;
		}
	};

	class Sequence : public CompositeNode {
	public:
		virtual Status Update() override {
			for (Node* child : GetChildren()) {
				if (child->Update() == Node::Status::Active)
					return Node::Status::Active;
				else if (child->Update() == Node::Status::Fail)
					return Node::Status::Fail;
			}
			return Node::Status::Ok;
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
		virtual Status Update() override { return getChild()->Update(); }
	};

	class Inverter : public DecoratorNode {  
	private:
		virtual Status Update() override 
		{ 
			if (Status::Ok) Status::Fail;
			else if(Status::Fail) Status::Ok;
			else return Status::Active; 
		}
	};

	class Conditional : public Node {
	private:
		std::function<bool()> callback;
	public:
		template <typename F>
		Conditional(F cb) : callback(cb) {}
	private:
		virtual Status Update() override {
			if (callback()) {
				return Node::Status::Ok;
			}
			return Node::Status::Fail;
		}
	};

	class Action : public Node {
	private:
		std::function<Node::Status()> callback;
	public:
		template <typename F>
		Action(F cb) : callback(cb) {}
	private:
		virtual Status Update() override { return callback(); }
	};

	class BehaviourTree
	{
	private:
		Root* m_root;
	public:
		BehaviourTree() : m_root(new Root) {}
		void setRootChild(Node* rootChild) const { m_root->setChild(rootChild); }
		bool Update() const { return m_root->Update(); }
	};
}