/* ASSUMPTIONS:
1. When a node must be split and has an odd number of keys, the extra key will go to the new right-hand node.
2. There will never be a duplicate key passed to insert.
*/
#include <algorithm>
#include <vector>

#ifndef DS_BPLUSTREE
#define DS_BPLUSTREE
using namespace std;

///////////////////////////////////////////////////////////////////////////////
//DO NOT CHANGE THIS CODE
///////////////////////////////////////////////////////////////////////////////
template <class T> class BPlusTree;

template <class T>
class BPlusTreeNode{
public:
	BPlusTreeNode() : parent(NULL) {};
	bool is_leaf();
	bool contains(const T& key);

	//For grading only, this is actually bad to have because
	//it exposes a private member variable.
	BPlusTreeNode* get_parent() { return parent; } 

	//We need this to let BPlusTree access private members
	friend class BPlusTree<T>; 
private:
	bool contains(const T& key,size_t low,size_t high);
	vector<T> keys;
	vector<BPlusTreeNode*> children;
	BPlusTreeNode* parent;
};

template <class T>
bool BPlusTreeNode<T>::is_leaf(){
	for(unsigned int i=0; i<children.size(); i++){
		if(children[i]){
			return false;
		}
	}
	return true;
}

template <class T>
bool BPlusTreeNode<T>::contains(const T& key){
	return contains(key,0,keys.size()-1);
}

//Private method takes advantage of the fact keys are sorted
template <class T>
bool BPlusTreeNode<T>::contains(const T& key,size_t low,size_t high){
	if(low>high){
		return false;
	}
	if(low==high){
		return key == keys[low];
	}
	size_t mid = (low+high)/2;
	if(key<=keys[mid]){
		return contains(key,0,mid);
	}
	else{
		return contains(key,mid+1,high);
	}
}

///////////////////////////////////////////////////////////////////////////////////////
//Your BPlusTree implementation goes below this point.
///////////////////////////////////////////////////////////////////////////////////////

template <class T>
class BPlusTree{

public:
	BPlusTree(int b_){ //default constructor
		root = NULL;
		b = b_;
		numKeys = b_-1; //max number of keys
		numChilds = b_; //max number of children
	}
	BPlusTree(const BPlusTree<T>& old){ //copy constructor
		root = this->copy_tree(old.root); //use my copy function to copy the tree
		b = old.b; //copies the private variable
		numKeys = old.numKeys;
		numChilds = old.numChilds;

	}
	BPlusTree& operator=(const BPlusTree<T>& old){//assignment operator
		if(&old != this){//checks if theyre equal
			this->destroy_tree(root); //destroys existing root
			root = this->copy_tree(old.root); //copies new roott
			b = old.b; //copies the private varible
			numKeys = old.numKeys;
			numChilds = old.numChilds;
		}
		return *this;
	}
	~BPlusTree(){this->destroy_tree(root); root =NULL;}//destructor
	// Returns true if this B+ tree has no keys or values.
    bool isEmpty() const{//checks if a tree is empty
	    return !root;
	}
	//inserts
    void insert(const T& key){
		if(isEmpty()){
			startNewTree(key);//starts a new tree if it is empty
		}
		else{
			insertIntoLeaf(key);//if its not an empty then it inserts it into the leaf
		}
	}
	//finds returns a pointer to the leaf the key is in or should be in if 
	BPlusTreeNode<T>* find(const T& key){
		if(isEmpty()){//if tree is empty its return a null pointer
			return NULL;
		}
		bool found = false;
		BPlusTreeNode<T>* curNode = root;
		while(!curNode->is_leaf()){// while loop until it reaches a leaf
			for(int i=0; i<curNode->keys.size();i++){ // for loop that runs through the key values
				if(key<curNode->keys[i]){ //sees if the key youre looking for is less
					curNode = curNode->children[i]; //if it is it reassigns the curNode to that pointer
					found = true;					//with in the children vector
					break;//break out of four loop
				}

			}
			if(found == false){//if found is false, the key is greater than all the key values
				curNode = curNode->children[-1];//assigns it to the last pointer
			}
		}
		if(curNode->is_leaf()){//makes sure its a leaf again
			return curNode;
		}

	}

	void insertIntoLeaf(const T& key){
		BPlusTreeNode<T>* leafNode = find(key);//finds the leaf it should be inserted int o
		leafNode->keys.push_back(key);// pushes back to the key vector of that leaf
		int size = leafNode->keys.size();
		if(size>numKeys){//if the keys now exceed the max number of keys
			int mid = size/2;//its splits
			vector<T> tempkeys = leafNode->keys;
				
		}
	}

	void print_sideways(ofstream& outfile){//print out sideways
		if(isEmpty()){
			outfile<<"Tree is empty."<<endl;
		}
	}
	void print_BFS(ofstream& outfile){
		if(isEmpty()){
			outfile<<"Tree is empty."<<endl;
		}
	}
	//These are thr functions I attempted to implament but could not succesfully
	// 	BPlusTreeNode<T>* splitLeaf( const vector<T>& keys){ //this splits the leaf node
	// 		BPlusTreeNode<T>* ChildNode2 = 	new  BPlusTreeNode<T>;//creates the new/second node
	// 		int mid = keys.size()/2;//finds the mid value, I would have pushed back the mid value into the parent nod
	// 		for(int i=mid;i<keys.size();i++){
	// 			ChildNode2->keys.push_back(keys[i]);//adds the appropriate keys to new node
	// 		}
	// 		return ChildNode2;
			// in my previous main code I kept the existing node that need splitting and used the
			//vector resize function to resize the keys/children to include the appropitrate values/pointers
	// 	}

		//when you split a non leaf you dont include the value you push up
	// 	BPlusTreeNode<T>* splitNonLeaf(const vector<T>& keys){ //split non leaf
	// 		BPlusTreeNode<T>* ChildNode2 = 	new  BPlusTreeNode<T>;
	// 		int mid = keys.size()/2;
	// 		for(int i=mid+1;i<keys.size();i++){
	// 			ChildNode2->keys.push_back(keys[i]);
	// 		}

	// 		return ChildNode2;

	// 	}

private: //private varibles
	int b;
	int numKeys;
	int numChilds;
	BPlusTreeNode<T>* root;

	BPlusTreeNode<T>* copy_tree(BPlusTreeNode<T>* old_root){//copy tree
		if(old_root == NULL){return NULL;} //if NULL just return NULL base case
		BPlusTreeNode<T>* new_root = new  BPlusTreeNode<T>;
		new_root->keys=old_root->keys;//copies keys
		new_root->parent=old_root->parent; //copies parent
		for(int i=0; i<old_root->children.size();i++){// reursivly goes through the children vector
		 	new_root->children[i]=copy_tree(old_root->children[i]); //calls the copy tree function
		}
		return new_root;//assignes new root and returns it
	}
	void startNewTree(const T& key) {//starts new tree if tree is empty
		BPlusTreeNode<T>* newTreeNode = new BPlusTreeNode<T>;
		newTreeNode->keys.push_back(key);//push back the keys
		newTreeNode->parent = NULL;//sets parent to null
		root = newTreeNode; //reasigns root
	}
	void destroy_tree(BPlusTreeNode<T>* old_root) { //destroy tree function
		if(!old_root){return;}//if root is NULL just return
		delete old_root->parent;//delete parent pointer
		for(int i=0; i<old_root->children.size();i++){//runs through all children and recursivley deletes it
		 	destroy_tree(old_root->children[i]);
		}
		delete old_root; //delete final root
	}
};
#endif