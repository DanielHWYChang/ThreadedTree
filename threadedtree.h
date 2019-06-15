/////////////////////////////////////////////////////////////////////
//File           : threadedtree.h
//Assignment     : 3
//Author         : Daniel Chang
//Student Number : 076470145
//Due Date       : Dec 9, 2016
/////////////////////////////////////////////////////////////////////
#include <iostream>
using namespace std;

template <class T>
class ThreadedTree{
	struct Node{
		T data_;
		bool leftthread_;
		bool rightthread_;
		Node* left_;
		Node* right_;
		
		Node(const T& data=T{},Node* left=nullptr, Node* right=nullptr){
			data_=data;
			left_=left;
			right_=right;
			leftthread_ = true;
			rightthread_ = true;
		}
	};
	Node* root_;	
	Node* head_;
	Node* tail_;
	void print(const Node* rt, int lvl)const{
		//I won't test this on the main.  You might find it useful
		//to implement for testing purposes
		//Note, passed in lvl so that you can use indentations based on lvl to 
		//see the level of a node is within your tree.  if you don't want to use it
		//just alter the prototype and call from print function

	}
	
	void cleanup(Node* subtreeroot){
		if(subtreeroot){
			if(!subtreeroot->leftthread_){
				cleanup(subtreeroot->left_);
			}
			
			if(!subtreeroot->rightthread_){
				cleanup(subtreeroot->right_);
			}

			delete subtreeroot;
		}
	}

public:
	class const_iterator{
	protected:
		Node* curr_;
		const_iterator(Node* c){curr_=c;}
	public:
		const_iterator(){
			curr_=nullptr;
		}
		
		//moves the const_iterator to the next largest node
		//and returns an const_iterator to the current node
		const_iterator operator++(int){
			const_iterator temp(curr_);
			if(curr_->rightthread_){
				curr_ = curr_->right_;
			}
			else{
				curr_ = curr_->right_;
				while(!curr_->leftthread_){
					curr_=curr_->left_;
				}
			}
			return temp;
		}
		
		//moves the const_iterator to the next smallest node
		//and returns an const_iterator to the current node
		const_iterator operator--(int){
			const_iterator temp(curr_);
			if(curr_->leftthread_){
				curr_ = curr_->left_;
			}
			else{
				curr_ = curr_->left_;
				while(!curr_->rightthread_){
					curr_=curr_->right_;
				}
			}
			return temp;
		}
		
		//moves the const_iterator to the next largest node
		//and returns an const_iterator to the new location
		const_iterator operator++(){
			if(curr_->rightthread_){
				curr_ = curr_->right_;
			}
			else{
				curr_ = curr_->right_;
				while(!curr_->leftthread_){
					curr_=curr_->left_;
				}
			}
			return const_iterator(curr_);
		}
		
		//moves the const_iterator to the next smallest node
		//and returns an const_iterator to the new location
		const_iterator operator--(){
			if(curr_->leftthread_){
				curr_ = curr_->left_;
			}
			else{
				curr_ = curr_->left_;
				while(!curr_->rightthread_){
					curr_=curr_->right_;
				}
			}
			return const_iterator(curr_);
		}
		
		const T& operator*(){
			return curr_->data_;
		}
		bool operator==(const const_iterator& rhs) const{
			return curr_ == rhs.curr_;
		}
		bool operator!=(const const_iterator& rhs) const{
			return curr_ != rhs.curr_;
		}
		friend class ThreadedTree;
	};
	
	
	class iterator:public const_iterator{
		iterator(Node* c):const_iterator(c){}
	public:
		iterator():const_iterator(){}
		const T& operator*(){
			return this->curr_->data_;
		}
		
		//moves the iterator to the next largest node
		//and returns an iterator to the current node
		iterator operator++(int){
			iterator temp(const_iterator::curr_);
			if(const_iterator::curr_->rightthread_){
				const_iterator::curr_ = const_iterator::curr_->right_;
			}
			else{
				const_iterator::curr_ = const_iterator::curr_->right_;
				while(!const_iterator::curr_->leftthread_){
					const_iterator::curr_=const_iterator::curr_->left_;
				}
			}
			return temp;
		}
		
		//moves the iterator to the next smallest node
		//and returns an iterator to the current node
		iterator operator--(int){
			iterator temp(const_iterator::curr_);
			if(const_iterator::curr_->leftthread_){
				const_iterator::curr_ = const_iterator::curr_->left_;
			}
			else{
				const_iterator::curr_ = const_iterator::curr_->left_;
				while(!const_iterator::curr_->rightthread_){
					const_iterator::curr_=const_iterator::curr_->right_;
				}
			}
			return temp;
		}
		
		//moves the iterator to the next largest node
		//and returns an iterator to the new location
		iterator operator++(){
			if(const_iterator::curr_->rightthread_){
				const_iterator::curr_ = const_iterator::curr_->right_;
			}
			else{
				const_iterator::curr_ = const_iterator::curr_->right_;
				while(!const_iterator::curr_->leftthread_){
					const_iterator::curr_=const_iterator::curr_->left_;
				}
			}
			return iterator(const_iterator::curr_);
		}
		
		//moves the iterator to the next smallest node
		//and returns an iterator to the new location
		iterator operator--(){
			if(const_iterator::curr_->leftthread_){
				const_iterator::curr_ = const_iterator::curr_->left_;
			}
			else{
				const_iterator::curr_ = const_iterator::curr_->left_;
				while(!const_iterator::curr_->rightthread_){
					const_iterator::curr_=const_iterator::curr_->right_;
				}
			}
			return iterator(const_iterator::curr_);
		}

		friend class ThreadedTree;
	};

	ThreadedTree(){
		root_ = nullptr;
		head_ = new Node();
		tail_ = new Node();
		head_->right_=tail_;
		tail_->left_=head_;
	}
	
	//takes a piece of data and inserts it into the tree
	//returns an iterator to the inserted node
	iterator insert(const T& data){
		Node* temp = new Node(data); //create node befor finding its location
		if(root_==nullptr){//link sentinels if you are inserting the root
			root_=new Node(data);
			root_->left_ = head_;
			head_->right_ = root_;
			root_->right_ = tail_;
			tail_->left_ = root_;
		}
		else{
			bool isInserted=false;
			Node* curr=root_;
			while(!isInserted){
				if(data < curr->data_){
					temp->right_ = curr;//set treads as you move through the tree
					if(curr->leftthread_==true){
						if(curr->left_ == head_){//set sentinels if inserting at ends of tree
							temp->left_ = head_;
							head_->right_ = temp;
						}
						curr->leftthread_ = false;
						curr->left_= temp;
						isInserted=true;
					}
					else{
						curr=curr->left_;
					}
				}
				else{
					temp->left_ = curr;//set treads as you move through the tree
					if(curr->rightthread_==true){
						if(curr->right_ == tail_){//set sentinels if inserting at ends of tree
							temp->right_ = tail_;
							tail_->left_ = temp;
						}
						curr->right_= temp;
						curr->rightthread_ = false;
						isInserted=true;
					}
					else{
						curr=curr->right_;
					}

				}
			}
		}
		return iterator(temp);
	}
	
	//searches for the given value in the tree and returns an iterator
	//to that location
	iterator find(const T& data) const{
		Node* curr = root_;
		bool found = false;
		while(!found){
			if(data < curr->data_ && !curr->leftthread_){
				curr = curr->left_;
			}
			else if(data > curr->data_ && !curr->rightthread_){
				curr = curr->right_;
			}
			else if(data == curr->data_){
				found = true;
			}
			else{
				return iterator(tail_);
			}
			
		}
		
		return iterator(curr);
	}
	
	//returns an iterator to the smallest node in tree
	iterator begin(){
		if(head_->right_){
			return iterator(head_->right_);
		}
		else{
			return iterator(nullptr);
		}
	}
	
	//returns an iterator to the node after the largest node in tree
	iterator end(){
		return iterator(tail_);
	}
	
	//returns a const_terator to the smallest node in tree
	const_iterator begin() const{
		if(head_->right_){
			return const_iterator(head_->right_);
		}
		else{
			return const_iterator(nullptr);
		}
		
	}
	
	//returns a const_iterator to the node after the largest node in tree
	const_iterator end() const{
		return const_iterator(tail_);
		
	}
	void print() const{
		const_iterator curr(head_->right_);
		while(curr != tail_){
			std::cout << *curr << " | ";
			curr++;
		}
	}
	~ThreadedTree(){
		cleanup(root_);
	}
};