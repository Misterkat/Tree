#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <stdio.h>

#include "tree.h"

int main(void){
	Localize();

	std::string info =
"����:\n \
[1] ������� ������\n \
[2] ����������� ������\n \
[3] ������\n \
[4] ����� �������\n \
[5] ���������� ���������� ����� ������\n \
[6] ���������� ���������� �������\n \
[7] ���������� ������� ����\n \
[8] ���������� ������� �������\n \
[9] ���������� ������� ������\n \
[10] ����� �������(�������)\n \
[11] ������� �������\n \
[12] ������� ������\n \
[13] ������� ������� � ������������\n \
[14] ����� � �������(�� �����������)\n \
[15] ����� � ������(�� �����������)\n \
[16] ������� ������� � ������� �� ��������� ���-�� �������� � ����� � ������ �����������\n\
[0] �����";

	Tree* T;
	int cmd = -1;
	while(cmd){
		WriteLn(info);
		Read("�������: ", cmd);
		switch(cmd){
			case 1:
				Read("������� ���-�� ���������: ", cmd);
				T = new Tree(cmd);
			break;
			case 2:
				T->PrintTree();
			break;
			case 3:
				T->DrawTree();
			break;
			case 4:
				Read("������� ������� �������: ", cmd);
				T->findElement(cmd);
			break;
			case 5:
				T->NodeCount();
			break;
			case 6:
				T->LeafCount();
			break;
			case 7:
				Read("������� ������� ����: ", cmd);
				T->CountNodeChilds(cmd);
			break;
			case 8:
				Read("������� ������� �������: ", cmd);
				T->CalculateNodeLevel(cmd);
			break;
			case 9:
				T->TreeDepthCount();
			break;
			case 10:
				Read("������� ������� �������:", cmd);
				T->InOrderSearch(cmd);
			break;
			case 11:
				Read("������� ������� �������:", cmd);
				T->RemoveNode(cmd);
			break;
			case 12:
				T->RemoveTree();
				WriteLn("������ �������, ��� ����������� ������ ��������� �������� ����� ������!");
			break;
			case 13:
				Read("������� ������� �������:", cmd);
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
					WriteLn("������������ �������("<< cmd << ")");
			break;
		}
		WriteLn("");
	}
	
	return 0;
}
