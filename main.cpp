#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <stdio.h>

#include "tree.h"

int main(void){
	Localize();

	std::string info =
"Меню:\n \
[1] Создать дерево\n \
[2] Распечатать дерево\n \
[3] Обходы\n \
[4] Найти элемент\n \
[5] Подсчитать количество узлов дерева\n \
[6] Подсчитать количество листьев\n \
[7] Подсчитать степень узла\n \
[8] Подсчитать уровень вершины\n \
[9] Подсчитать глубину дерева\n \
[10] Найти элемент(обходом)\n \
[11] Удалить элемент\n \
[12] Удалить дерево\n \
[13] Удалить элемент с перестройкой\n \
[14] Обход в глубину(не рекурсивный)\n \
[15] Обход в ширину(не рекурсивный)\n \
[16] Вывести вершины у которых не совпадает кол-во потомков в левом и правом поддеревьях\n\
[0] Выход";

	Tree* T;
	int cmd = -1;
	while(cmd){
		WriteLn(info);
		Read("Команда: ", cmd);
		switch(cmd){
			case 1:
				Read("Введите кол-во элементов: ", cmd);
				T = new Tree(cmd);
			break;
			case 2:
				T->PrintTree();
			break;
			case 3:
				T->DrawTree();
			break;
			case 4:
				Read("Введите искомый элемент: ", cmd);
				T->findElement(cmd);
			break;
			case 5:
				T->NodeCount();
			break;
			case 6:
				T->LeafCount();
			break;
			case 7:
				Read("Введите целевой узел: ", cmd);
				T->CountNodeChilds(cmd);
			break;
			case 8:
				Read("Введите целевую вершину: ", cmd);
				T->CalculateNodeLevel(cmd);
			break;
			case 9:
				T->TreeDepthCount();
			break;
			case 10:
				Read("Введите целевую вершину:", cmd);
				T->InOrderSearch(cmd);
			break;
			case 11:
				Read("Введите целевую вершину:", cmd);
				T->RemoveNode(cmd);
			break;
			case 12:
				T->RemoveTree();
				WriteLn("Дерево удалено, для продолдения работы программы создайте новое дерево!");
			break;
			case 13:
				Read("Введите целевую вершину:", cmd);
				T->RemoveNodeWithReconstruction(cmd);
			break;
			case 14:
				T->NotRecursiveInOrder();
			break;
			case 15:
				T->NotRecursiveObhod();
			break;
			case 16:
				T->III();
			break;
			case 17:
				T->BalanceTree();
			break;
			default:
				if(cmd)
					WriteLn("Недопустимая команда("<< cmd << ")");
			break;
		}
		WriteLn("");
	}
	
	return 0;
}
