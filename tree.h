#include <iostream>
#include <vector>
#include <string>
#include <windows.h>

#include "fx.h"
#include "stack.h"
#include "queue.h"

class Tree{
private:
	typedef std::string str;
	typedef std::vector<int> vecint;

	template<typename T>
	struct rv{
		T value;
		T* pointer;
	};

	struct TreeType{
		int data;
		TreeType
			*left,
			*right;
	};

	TreeType* TreeRoot;
	bool newTree;
	int treeSize;

	void RecursiveDeleteElement(TreeType* TP){
		if(TP->left) RecursiveDeleteElement(TP->left);
		if(TP->right) RecursiveDeleteElement(TP->right);
		delete TP;
	}

	rv<bool> RecursiveInOrderSearch(int data, TreeType* TP){
		static bool found = false;
		if(data == TP->data)
			found = true;
		if(TP->left) RecursiveInOrderSearch(data, TP->left);
		if(TP->right) RecursiveInOrderSearch(data, TP->right);
		return {found, &found};
	}

	void vInc(vecint* vec){
		if(!vec->size())
			vec->push_back(1);
		int lastElement = vec->back();
		lastElement++;
		vec->pop_back();
		vec->push_back(lastElement);
	}

	int FindBiggest(vecint* vec){
		int max = 0;
		for(int i = 0; i < vec->size(); i++){
			int last = vec->back();
			if(max < last) max = last;
			vec->pop_back();
		}
		return max;
	}

	void Swap(TreeType* A, TreeType* B){
		TreeType* C;
		C = A;
		A = B;
		B = C;
	}

	int ITD(TreeType* TP){ //TreeDepth
		rv<vecint*> tmp = RecursiveTreeDepthCount(TreeRoot);
		int Depth = FindBiggest(tmp.value);
		(*(tmp.pointer))->clear();
		return Depth;
	}

//################################################
	void RecursiveBalanceTree(TreeType* TP){
		if((ITD(TP->left) == 2) && (ITD(TP->right->left) <= ITD(TP->right->right))){
			TreeType
				*L = TP->left,
				*C = TP->right->left,
				*R = TP->right->right,
				*a = TP,
				*b = TP->right;

			a->left = L;
			a->right = C;
			b->right = R;
			b->left = a;
		}

		if(TP->left) RecursiveBalanceTree(TP->left);
		if(TP->right) RecursiveBalanceTree(TP->right);
	}
//###############################################
	rv<vecint*> RecursiveTreeDepthCount(TreeType* TP){
		static vecint* Depth = new vecint;

		vInc(Depth);

		if(!TP->left && !TP->right)
			Depth->push_back(1);

		if(TP->left) RecursiveTreeDepthCount(TP->left);
		if(TP->right) RecursiveTreeDepthCount(TP->right);
		return {Depth, &Depth};
	}

	//Прямой обход
	rv<str> RecursivePreOrder(TreeType* TP){
		static str result = "";
		char s[6];

		memset(&s, 0, sizeof(s));
		sprintf(s, "%d-", TP->data);
		result += s;

		if(TP->left) RecursivePreOrder(TP->left);
		if(TP->right) RecursivePreOrder(TP->right);

		return {result.substr(0, result.length()-1), &result};
	}
	
	//Обратный обход
	rv<str> RecursiveInOrder(TreeType* TP){
		static str result = "";
		char s[6];

		memset(&s, 0, sizeof(s));
		

		if(TP->left) RecursiveInOrder(TP->left);
		if(TP->right) RecursiveInOrder(TP->right);

		sprintf(s, "%d-", TP->data);
		result += s;

		return {result.substr(0, result.length()-1), &result};
	}
	
	//Симметричный обход
	rv<str> RecursiveObhod(TreeType* TP){
		static str result = "";
		char s[6];

		memset(&s, 0, sizeof(s));
		
		if(TP->left) RecursiveObhod(TP->left);

		sprintf(s, "%d-", TP->data);
		result += s;

		if(TP->right) RecursiveObhod(TP->right);
		
		return {result.substr(0, result.length()-1), &result};
	}

	void RecursiveAdd(TreeType* TP, int data){
		if(newTree){
			TreeRoot = new TreeType;
			TreeRoot->left = TreeRoot->right = 0;

			TreeRoot->data = data;
			newTree = false;
			return;
		}

		if(data > TP->data)
			if(TP->right)
				RecursiveAdd(TP->right, data);
			else{
				TP->right = new TreeType;
				TP->right->data = data;
				TP->right->left = TP->right->right = 0;
			}
		else
			if(TP->left)
				RecursiveAdd(TP->left, data);
			else{
				TP->left = new TreeType;
				TP->left->data = data;
				TP->left->left = TP->left->right = 0;
			}
	}
	
	rv<int> RecursiveCountChilds(TreeType* TP, bool left, bool recursiveCall = false){
		static int c = 0;
		
		if(recursiveCall && TP){
			c++;
			RecursiveCountChilds(TP->left, true, true);
			RecursiveCountChilds(TP->right, true, true);
		}
		
		if(left && TP){
			c++;
			RecursiveCountChilds(TP->left, true, true);
		}else if (TP){
			c++;
			RecursiveCountChilds(TP->right, true, true);
		}
		return {c, &c};
	}
	
	int IRecursiveCountChilds(TreeType* TP, bool left){
		rv<int> RCC = RecursiveCountChilds(TP, left);
		*(RCC.pointer) = 0;
		return RCC.value;
	}

	rv<str> RecursiveCountDifferentChildCount(TreeType* TP){
		static str rtn = "";
		if(IRecursiveCountChilds(TP, true) != IRecursiveCountChilds(TP, false))
			rtn += "[" + std::to_string(TP->data) + "]-";

		if(TP->left) RecursiveCountDifferentChildCount(TP->left);
		if(TP->right) RecursiveCountDifferentChildCount(TP->right);
		return {rtn.substr(0, rtn.size()-1), &rtn};
	}
	
	TreeType* GetPointerToPrevNode(TreeType* TP, TreeType* NP){
		if(TP->left == NP || TP->right)
			return TP;
		else{
			if(TP->left) GetPointerToPrevNode(TP->left, NP);
			if(TP->right) GetPointerToPrevNode(TP->right, NP);
		}
		return 0;
	}

	void RecursivePrintTree(TreeType *TP, long n = 0){
		if (TP){
			RecursivePrintTree(TP->right, n+5);
			for (int i = 0; i < n; i++) 
				Write(" ");
			WriteLn(TP->data);
			RecursivePrintTree(TP->left, n+5);
		}
	}

	rv<str> RecursiveFindElement(int data, TreeType* TP){
		static str path = "К", result = "Элемент не найден";

		char c[32];
		memset(&c, 0, sizeof(c));

		if(data == TP->data){
			sprintf(c, "Элемент [%d] найден по пути: %s", data, path.c_str());
			result = "";
			result += c;
			path = "K";
			return {result, &result}; //На случай, если элемент оказался в корне
		}

		if((data > TP->data) && TP->right){
			path += str("-П");
			RecursiveFindElement(data, TP->right);
		}
		else if(TP->left){
			path += str("-Л");
			RecursiveFindElement(data, TP->left);
		}
		else{
			path = "K";
			return {str(""), &result};
		}
		path = "К";
		return {result, &result};
	}

	rv<int> RecursiveNodeCounter(TreeType* TP){
		static int i = 0;
		i++;
		if(TP->left) RecursiveNodeCounter(TP->left);
		if(TP->right) RecursiveNodeCounter(TP->right);
		return {i, &i};
	}

	rv<int> RecursiveLeafCounter(TreeType* TP){
		static int i = 0;

		if(!TP->left && !TP->right) i++;

		if(TP->left) RecursiveLeafCounter(TP->left);
		if(TP->right) RecursiveLeafCounter(TP->right);
		return {i, &i};
	}

	rv<TreeType*> GetNodePointer(int data, TreeType* TP){
		static TreeType* FoundedNodePointer = 0;
		if(TP->data == data) FoundedNodePointer = TP;
		if(TP->left) GetNodePointer(data, TP->left);
		if(TP->right) GetNodePointer(data, TP->right);
		return {FoundedNodePointer, &FoundedNodePointer};
	}

	int CountSingleNodeChilds(TreeType* TP){
		if(TP->left && TP->right) return 2;
		else if(TP->left || TP->right) return 1;
		else return 0;
	}

	rv<int> RecursiveCountNodeChilds(TreeType* TP){
		static int v = 0;
		int nMax = CountSingleNodeChilds(TP);
		v = (v < nMax) ? nMax : v;

		if(TP->left) RecursiveCountNodeChilds(TP->left);
		if(TP->right) RecursiveCountNodeChilds(TP->right);
		
		return {v, &v}; //Поскульку вернуть нужно большее значение, а очистить стат. переменную
	}

	rv<vecint> RecursivePopFromNode(TreeType* TP){
		static vecint data;
		data.push_back(TP->data);
		if(TP->left) RecursivePopFromNode(TP->left);
		if(TP->right) RecursivePopFromNode(TP->right);
		return {data, &data};
	}

public:
	Tree(int size){
		newTree = true;
		this->treeSize = size;
		Randomize();
		FillTree();	
	}~Tree(){}
	
	//Обход дерева в глубину
	void NotRecursiveInOrder(){
		Stack<TreeType*>* S = new Stack<TreeType*>(treeSize*3);
		TreeType* Poped;
		str lmnts = "";
		S->Push(TreeRoot);
		do{
			Poped = S->Pop();
			if(!Poped) break;
			if(Poped->left) S->Push(Poped->left);
			if(Poped->right) S->Push(Poped->right);
			lmnts += "[" + std::to_string(Poped->data) + "]-";
		} while(1);
		lmnts.resize(lmnts.size()-1);
		WriteLn(lmnts);
	}

	//Обход дерева в ширину
	void NotRecursiveObhod(){
		Queue<TreeType*>* Q = new Queue<TreeType*>(treeSize*3);
		TreeType* Poped;
		str lmnts = "";

		Q->Push(TreeRoot);
		do{
			Poped = Q->Pop();
			if(!Poped) break;
			if(Poped->left) Q->Push(Poped->left);
			if(Poped->right) Q->Push(Poped->right);
			lmnts += "[" + std::to_string(Poped->data) + "]-";
		}while(1);

		lmnts.resize(lmnts.size()-1);
		WriteLn(lmnts);
	}

	void RemoveNode(int data){
		rv<TreeType*> tmp = GetNodePointer(data, TreeRoot);
		TreeType
			*currentNode = tmp.value,
			*prevNode = GetPointerToPrevNode(TreeRoot, currentNode);

		(data > prevNode->data) ? prevNode->right : prevNode->left = 0;

		*(tmp.pointer) = 0;

		RecursiveDeleteElement(currentNode);
	}

	void RemoveNodeWithReconstruction(int data){
		rv<TreeType*> NP = GetNodePointer(data, TreeRoot);

		TreeType
			*currentNode = NP.value,
			*prevNode = GetPointerToPrevNode(TreeRoot, currentNode);
		*(NP.pointer) = 0;

		if(currentNode->right && !currentNode->left)
			if(currentNode->data > prevNode->data)
				prevNode->right = currentNode->right;
			else
				prevNode->left = currentNode->right;
		else if(currentNode->left && !currentNode->right)
			if(currentNode->data > prevNode->data)
				prevNode->right = currentNode->left;
			else
				prevNode->left = currentNode->left;
		else if(!currentNode->left && !currentNode->right)
			if(currentNode->data > prevNode->data)
				prevNode->right = 0;
			else
				prevNode->left = 0;
		else{
			if(currentNode->data > prevNode->data)
				prevNode->right = 0;
			else
				prevNode->left = 0;
			rv<vecint> data = RecursivePopFromNode(currentNode);
			for(int i = 0; i < data.value.size(); i++){
				Add(data.value.back());
				data.value.pop_back();
			}
			data.pointer->clear();
			
		}
		delete currentNode;
	}

	void RemoveTree(){
		RecursiveDeleteElement(TreeRoot);
	}

	void CalculateNodeLevel(int data){
		int level = 1;
		TreeType* TP = TreeRoot;

		while(TP){
			if(TP->data == data){
				WriteLn("Вершина [" << data << "] находится на " << level << " уровне");
				return;
			}
			if((data > TP->data) && TP->right){
				TP = TP->right;
				level++;
			}
			else if(TP->left){
				TP = TP->left;
				level++;
			}
		}
		WriteLn("Вершина [" << data << "] не найдена");
	}

	void findElement(int data){
		rv<str> tmp = RecursiveFindElement(data, TreeRoot);
		WriteLn(tmp.value);
		tmp.pointer->clear();
	}

	void FillTree(){
		str inputedData = "";
		char c[5];
		memset(&c, 0, sizeof(c));

		for(int i = 0; i < treeSize; i++){
			int tmp = rand()%(treeSize*10);
			sprintf(c, "[%d] ", tmp);
			inputedData += c;
			Add(tmp);
		}
		WriteLn("Испольуемые данные: " << inputedData);
	}

	void Add(int data){
		RecursiveAdd(TreeRoot, data);
	}
	
	void NodeCount(){
		rv<int> tmp = RecursiveNodeCounter(TreeRoot);
		WriteLn("Найдено " << tmp.value << " узлa(ов)");
		*(tmp.pointer) = 0;
	}

	void LeafCount(){
		rv<int> tmp = RecursiveLeafCounter(TreeRoot);
		WriteLn("Найдено " << tmp.value << " листа(ов)");
		*(tmp.pointer) = 0;
	}

	void InOrderSearch(int data){
		rv<bool> tmp = RecursiveInOrderSearch(data, TreeRoot);
		WriteLn("Эелемент [" << data << "] " << str( tmp.value ? "найден" : "не найден").c_str());
		*tmp.pointer = false;
	}

	void TreeDepthCount(){
		rv<vecint*> tmp = RecursiveTreeDepthCount(TreeRoot);
		WriteLn("Глубина дерева: " << FindBiggest(tmp.value));
		(*(tmp.pointer))->clear();
	}

	void CountNodeChilds(int data){
		rv<TreeType*> NP = GetNodePointer(data, TreeRoot);
		rv<int> tmp = RecursiveCountNodeChilds(NP.value);
		if(NP.value)
			WriteLn("Степень вершины [" << data << "] = " << tmp.value);
		else
			WriteLn("Вершина не найдена");
		*(tmp.pointer) = 0;
		*(NP.pointer) = 0;
	}

	void BalanceTree(){
		//RecursiveBalanceTree(TreeRoot);
	}

	void DrawTree(){
		rv<str> tmp;

		tmp = RecursivePreOrder(TreeRoot);
		WriteLn("Прямой обход: " << tmp.value);
		tmp.pointer->clear();

		tmp = RecursiveInOrder(TreeRoot);
		WriteLn("Обратный обход: " << tmp.value);
		tmp.pointer->clear();

		tmp = RecursiveObhod(TreeRoot);
		WriteLn("Симметричный обход: " << tmp.value);
		tmp.pointer->clear();
	}
	
	void PrintTree(){
		WriteLn("Графическое представление дерева(повернуто на 90 град. против часовой стрелки): ");
		RecursivePrintTree(TreeRoot);
	}	
	
	void III(){
		rv<str> s = RecursiveCountDifferentChildCount(TreeRoot);
		WriteLn(s.value);
		s.pointer->clear();
	}
	
	/*int XI(){
		return FindPath(TreeRoot);
	}*/
	
};
