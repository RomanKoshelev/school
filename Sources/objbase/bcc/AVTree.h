/*
________________________________________________________________________________
[]                                                                            []
[] This is a part of the PROJECT: 'AVTree'												[]
[] Copyright (C) 1999 W:Brain Software Inc.                                   []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            AVTree.h																	[]
[] Date:            21.03.99                                                  []
[] Author:          Ivan N. Ivanov															[]
[] Description:     �������� ������ ��������-���������								[]
[]____________________________________________________________________________[]
*/



/*______________________________________________________________________________
[]                                                                            []
[]  �������� ������ ��������-���������														[]
[] 																									[]
[]  KEY_TYPE	-- ��� �����. ������ ���� ����� ����� ������ ������				[]
[]  ITEM_TYPE	-- ��� ���������, ���������� � ������									[]
[]  PMKEY_TYPE -- ������ ���� ����� ��������� �� ���� ������						[]
[]						��������������� ��������� �� ����, � ����������� ���			[]
[]						KEY_TYPE ITEM_TYPE::*													[]
[]                                                                            []
[]----------------------------------------------------------------------------[]
[]																										[]
[]						struct X {int i;};														[]
[]						int cmpFunc (int& a, int& b) {return a<b? -1: a==b? 0: +1;}	[]
[]						IT_AVTree<X, int, int X::*> AVTree(&X::i, cmpFunc);			[]
[]																										[]
[]____________________________________________________________________________[]
*/

typedef void* item_pointer;

template <class ITEM_TYPE, class KEY_TYPE, class PMKEY_TYPE>
class IT_AVTree
{
	struct IT_AVTreeNode
	{
		IT_AVTreeNode *	Left;
		IT_AVTreeNode *	Right;
		IT_AVTreeNode *	Parent;
		ITEM_TYPE			Item;
		BYTE					Depth;
	};  
	IT_AVTreeNode *		Root;
	int						count;
	PMKEY_TYPE				PointMem;
	typedef KEY_TYPE&		KEY_TYPE_REF;
	typedef ITEM_TYPE&	ITEM_TYPE_REF;

	int (*CompareFunction)(KEY_TYPE_REF, KEY_TYPE_REF);
	

	protected:
	// ���������, ������������ ����� ��������-��������� ��� ����������� ������������� ������
		void AVProc(void *);		
	
	public:
	// ����� ������� ��������
		bool GetDepth(void *Pointer, int *Depth); 
	//____________________________________________________________________________[]









	//______________________________________________________________________________
	//                                                                            []
	//` ���������:																						[]
	//                                                                            []
	public:

	// �����������
		IT_AVTree(PMKEY_TYPE, int (*cmpFunc)(KEY_TYPE_REF, KEY_TYPE_REF));
		~IT_AVTree() {RemoveAll();}
		
	// ����� ��������� � ������
		int Count()		const {return count;};
		int Size()		const {return Count();};
		int GetSize()  const {return Count();};

	// ������ �����
		bool IsEmpty() {return count==0;};

	// �������� ������� � ������ (������ Item ����������)
		item_pointer Insert(ITEM_TYPE_REF Item);

	// ����� ����� ������ �������
		item_pointer First();

	// ����� ��������� �������
		item_pointer Next(item_pointer); 

	// ����� ����� ��������� �������
		item_pointer Last();

	// ����� ���������� �������
		item_pointer Prev(item_pointer);

	// ����� �� ����� ������ �������
		item_pointer Find(KEY_TYPE_REF Key, bool bInexact=false);

	// ����� ��������� ������� � ��� �� ������
		item_pointer NextWithSameKey(item_pointer Pointer);

	// ����� ���������� ������� � ��� �� ������
		item_pointer PrevWithSameKey(item_pointer Pointer);
		
	// ����� ��������� �� ��� ������� ��� ������
	// � ��� � ������ (�� ���������).
	// �� � ���� ������ �� ������ ����!!
	// (��� ����� ����� ������� ������� ��
	// ������, �������� ���� � ����� ��������
	// � ������.)
		ITEM_TYPE *ItemPointer(item_pointer Pointer) 
		{
			if (Pointer)
			{
				IT_AVTreeNode * pAVTreeNode = (IT_AVTreeNode *) Pointer;
				return &(pAVTreeNode->Item);
			}
			return NULL;
		};
		
	// �������� ����� ��������
		bool CopyTo(item_pointer Pointer, ITEM_TYPE_REF Item);

	// ������� ������� �� ������
		bool Remove(item_pointer Pointer);

	// �������� ������� ������ �� ������
		item_pointer Replace(item_pointer Pointer, ITEM_TYPE_REF Item);

	// �������� ������
		bool RemoveAll();

	// ������ �����, ����������� ��� ������ ������
		size_t GetBinarySize ()
		{
			return size_t (count*sizeof(ITEM_TYPE) + ((count+15)/16)*4);
		}

	// ������ ������, �������� �������������� ������/���������� ������
		size_t GetBinaryBlockSize ()
		{
			return size_t (4+16*(sizeof(ITEM_TYPE)));
		}

	// ������������� ������ � �������� �������������, �� �������� ��������
	// �������������� ����� ������ �� ������.
	// �������������� �������������� ������� �� 4+16*(sizeof(ITEM_TYPE)) ����.
	// ������� bool (*OutFunc)(BYTE *OutBlock) ���������� ���� ������
	// �� ����������. ���������� false ��� ������ ������.
	// ��������! (RVK)
	//		������������ ���� ������� ����� ������ ���� ITEM_TYPE �� ��������
	//		���������� � �� �������� ���������� ������ ����
		bool ConvertTreeToBinaryData (bool (*OutFunc)(BYTE *OutBlock, int NumInBlock));

		
	// ���������� �������������� �� ��������� ������������� � ������.
	// �������������� �������������� ������� �� 4+16*(sizeof(ITEM_TYPE)) ����.
	// ������� bool (*InFunc)(ITEM_TYPE *InBlock) ��������� ���� ������
	// ��� �������������� � ������. ���������� false ��� ������ ������.
	// ��������! (RVK)
	//		������������ ���� ������� ����� ������ ���� ITEM_TYPE �� ��������
	//		���������� � �� �������� ���������� ������ ����
		bool ConvertBinaryDataToTree (bool (*InFunc)(BYTE *InBlock));

	// 																									[]
	// ����� ����������																				[]
	//____________________________________________________________________________[]













	protected: 	bool ConvertBinaryDataToNode (bool (*InFunc)(BYTE *OutBlock), BYTE *BinaryBlock, IT_AVTreeNode **CurNode, int *NumInBlock, BYTE *Depth)
	{
		DWORD Bits;
		IT_AVTreeNode *Node;
		BYTE MaxDepth=1;
		BYTE Depth_;
		
		Bits=(*((DWORD *)BinaryBlock) >> (*NumInBlock*2)) & 3;
		
		(**CurNode).Item=*((ITEM_TYPE *)(BinaryBlock+4+sizeof(ITEM_TYPE)*(*NumInBlock)));
		
		// ����� ����������
		if((Bits & 2)==2)
		{
			if(++(*NumInBlock)>=16)
			{
				// ��������� ����
				if(!(*InFunc)(BinaryBlock))
					return false;
				*NumInBlock=0;
			}
			
			Node = new IT_AVTreeNode;
			if(Node==NULL)
				return false;
			(**CurNode).Left=Node;
			Node->Parent=*CurNode;
			count++;
			
			*CurNode=Node;
			if(!ConvertBinaryDataToNode(InFunc, BinaryBlock, CurNode,
				NumInBlock, &Depth_))
				return false;
			if(Depth_>MaxDepth)
				MaxDepth=Depth_;
		}
		else
			(**CurNode).Left=NULL;
		
		if((Bits & 1)==1)
		{
			if(++(*NumInBlock)>=16)
			{
				// ��������� �����
				if(!(*InFunc)(BinaryBlock))
					return false;
				*NumInBlock=0;
			}
			
			Node = new IT_AVTreeNode;
			if(Node==NULL)
				return false;
			(**CurNode).Right=Node;
			Node->Parent=*CurNode;
			count++;
			
			*CurNode=Node;
			if(!ConvertBinaryDataToNode(InFunc, BinaryBlock, CurNode,
				NumInBlock, &Depth_))
				return false;
			if(Depth_>MaxDepth)
				MaxDepth=Depth_;
		}
		else
			(**CurNode).Right=NULL;
		
		*Depth=(BYTE)(MaxDepth+1);
		(**CurNode).Depth=MaxDepth;
		
		if((**CurNode).Parent!=NULL)
			*CurNode=(**CurNode).Parent;
		
		return true;
	}
	protected: bool ConvertNodeToBinaryData (bool (*OutFunc)(BYTE *OutBlock, int NumInBlock), BYTE *BinaryBlock, IT_AVTreeNode **CurNode, int *NumInBlock)
	{
		DWORD Bits=0;
		
		if((**CurNode).Left!=NULL)
			Bits|=2;
		if((**CurNode).Right!=NULL)
			Bits|=1;
		
		Bits=(Bits << (*NumInBlock*2));
		
		*((DWORD *)BinaryBlock) |= Bits;

		// 09.08.99 RomanVK: 
		//	��� �������������� ������ ��������� ������������ �������� ������:
		// ����:
		//*((ITEM_TYPE *)(BinaryBlock+4+sizeof(ITEM_TYPE)*(*NumInBlock))) = (**CurNode).Item;
		// �����:
			memcpy (BinaryBlock+4+sizeof(ITEM_TYPE)*(*NumInBlock), &((**CurNode).Item), sizeof (ITEM_TYPE));

		if(++(*NumInBlock)>=16)
		{
			// ���� ��������
			
			if(!(*OutFunc)(BinaryBlock, *NumInBlock))
				return false;
			*NumInBlock=0;
			*((DWORD *)BinaryBlock)=0;
		}
		
		// ����� ����������
		if((**CurNode).Left!=NULL)
		{
			*CurNode=(**CurNode).Left;
			if(!ConvertNodeToBinaryData(OutFunc, BinaryBlock, CurNode, NumInBlock))
				return false;
		}
		if((**CurNode).Right!=NULL)
		{
			*CurNode=(**CurNode).Right;
			if(!ConvertNodeToBinaryData(OutFunc, BinaryBlock, CurNode, NumInBlock))
				return false;
		}
		
		if((**CurNode).Parent!=NULL)
			*CurNode=(**CurNode).Parent;
		
		return true;
	}
};
//____________________________________________________________________________[]















































//______________________________________________________________________________
//                                                                            []
//` � � � � � � �																					[]
//                                                                            []
template <class ITEM_TYPE, class KEY_TYPE, class PMKEY_TYPE>
IT_AVTree<ITEM_TYPE, KEY_TYPE, PMKEY_TYPE>::
IT_AVTree(PMKEY_TYPE pm, int (*cmpFunc)(KEY_TYPE&, KEY_TYPE&))
{
	PointMem=pm;
	CompareFunction=cmpFunc;
	Root=NULL;
	count=0;
}


template <class ITEM_TYPE, class KEY_TYPE, class PMKEY_TYPE>
void IT_AVTree<ITEM_TYPE, KEY_TYPE, PMKEY_TYPE>::
AVProc(void *Pointer)
{
	IT_AVTreeNode *p;
	IT_AVTreeNode *p2;
	IT_AVTreeNode *p3;
	IT_AVTreeNode *Parent;
	BYTE OldDepth;
	BYTE LDepth;
	BYTE RDepth;
	
	//printf("AVProc\n");
	p=(IT_AVTreeNode *)Pointer;
	OldDepth=p->Depth;
	
	if(p->Left==NULL)
		LDepth=0;
	else
		LDepth=(p->Left)->Depth;
	if(p->Right==NULL)
		RDepth=0;
	else
		RDepth=(p->Right)->Depth;
	
	p->Depth = (BYTE) ((LDepth>=RDepth) ? LDepth+1: RDepth+1);
	
	//printf("LDepth=%d, RDepth=%d\n", LDepth, RDepth);
	
	if(LDepth-RDepth>1 ||
      RDepth-LDepth>1)
	{
		//printf("���������������\n");
		// ���������������
		Parent=p->Parent;
		if(LDepth>RDepth)
		{
			// ��������� �����
			//printf("��������� �����\n");
			if(p->Right==NULL)
			{
				p2=p->Left;
				if(p2->Right==NULL)
				{
					p3=p2->Left;
					
					p2->Parent=Parent;
					if(Parent!=NULL)
					{
						if(Parent->Left==p)
							Parent->Left=p2;
						else
							Parent->Right=p2;
					}
					else
						Root=p2;
					p2->Left=p3;
					p3->Parent=p2;
					p2->Right=p;
					p->Parent=p2;
					p->Left=NULL;
					
					p3->Depth=1;
					p->Depth=1;
					p2->Depth=2;
					p=p2;
				}
				else
				{
					p3=p2->Right;
					
					p3->Parent=Parent;
					if(Parent!=NULL)
					{
						if(Parent->Left==p)
							Parent->Left=p3;
						else
							Parent->Right=p3;
					}
					else
						Root=p3;
					p3->Left=p2;
					p2->Parent=p3;
					p3->Right=p;
					p->Parent=p3;
					p->Left=NULL;
					p->Right=NULL;
					p2->Right=NULL;   //
					
					if(p2->Left==NULL)
					{
						p2->Depth=1;
						p->Depth=1;
						p3->Depth=2;
					}
					else
					{
						p2->Depth=2;
						p->Depth=1;
						p3->Depth=3;
					}
					p=p3;
				}
			}
			else
			{
				p2=p->Left;
				p3=p2->Right;
				if((p2->Left)->Depth>=p3->Depth)
				{
					p2->Parent=Parent;
					if(Parent!=NULL)
					{
						if(Parent->Left==p)
							Parent->Left=p2;
						else
							Parent->Right=p2;
					}
					else
						Root=p2;
					p2->Right=p;
					p->Parent=p2;
					p->Left=p3;
					p3->Parent=p;
					
					p->Depth  = (BYTE) (p3->Depth>=(p->Right)->Depth ? p3->Depth+1 : (p->Right)->Depth+1);
					p2->Depth = (BYTE) (p->Depth>=(p2->Left)->Depth ? p->Depth+1 : (p2->Left)->Depth+1);
					p=p2;
				}
				else
				{
					p3->Parent=Parent;
					if(Parent!=NULL)
					{
						if(Parent->Left==p)
							Parent->Left=p3;
						else
							Parent->Right=p3;
					}
					else
						Root=p3;
					if(p3->Left==NULL)
						p2->Right=NULL;
					else
					{
						p2->Right=p3->Left;
						(p3->Left)->Parent=p2;
					}
					if(p3->Right==NULL)
						p->Left=NULL;
					else
					{
						p->Left=p3->Right;
						(p3->Right)->Parent=p;
					}
					p3->Left=p2;
					p2->Parent=p3;
					p3->Right=p;
					p->Parent=p3;
					
					if(p2->Right==NULL)
						p2->Depth = (BYTE) ((p2->Left)->Depth+1);
					else
						p2->Depth = (BYTE) ((p2->Left)->Depth>=(p2->Right)->Depth ? (p2->Left)->Depth+1 : (p2->Right)->Depth+1);
					if(p->Left==NULL)
						p->Depth = (BYTE) ((p->Right)->Depth+1);
					else
						p->Depth = (BYTE) ((p->Left)->Depth>=(p->Right)->Depth ? (p->Left)->Depth+1 : (p->Right)->Depth+1);
					p3->Depth = (BYTE) (p2->Depth>=p->Depth ? p2->Depth+1 : p->Depth+1);
					p=p3;
				}
			}
    }
    else
    {
		 // ��������� ������
		 //  printf("��������� ������\n");
		 if(p->Left==NULL)
		 {
			 p2=p->Right;
			 if(p2->Left==NULL)
			 {
				 p3=p2->Right;
				 
				 p2->Parent=Parent;
				 if(Parent!=NULL)
				 {
					 if(Parent->Right==p)
						 Parent->Right=p2;
					 else
						 Parent->Left=p2;
				 }
				 else
					 Root=p2;
				 p2->Right=p3;
				 p3->Parent=p2;
				 p2->Left=p;
				 p->Parent=p2;
				 p->Right=NULL;
				 
				 p3->Depth=1;
				 p->Depth=1;
				 p2->Depth=2;
				 p=p2;
			 }
			 else
			 {
				 p3=p2->Left;
				 
				 p3->Parent=Parent;
				 if(Parent!=NULL)
				 {
					 if(Parent->Right==p)
						 Parent->Right=p3;
					 else
						 Parent->Left=p3;
				 }
				 else
					 Root=p3;
				 p3->Right=p2;
				 p2->Parent=p3;
				 p3->Left=p;
				 p->Parent=p3;
				 p->Right=NULL;
				 p->Left=NULL;
				 p2->Left=NULL;   //
				 
				 if(p2->Right==NULL)
				 {
					 p2->Depth=1;
					 p->Depth=1;
					 p3->Depth=2;
				 }
				 else
				 {
					 p2->Depth=2;
					 p->Depth=1;
					 p3->Depth=3;
				 }
				 p=p3;
			 }
		 }
		 else
		 {
			 p2=p->Right;
			 p3=p2->Left;
			 if((p2->Right)->Depth>=p3->Depth)
			 {
				 p2->Parent=Parent;
				 if(Parent!=NULL)
				 {
					 if(Parent->Right==p)
						 Parent->Right=p2;
					 else
						 Parent->Left=p2;
				 }
				 else
					 Root=p2;
				 p2->Left=p;
				 p->Parent=p2;
				 p->Right=p3;
				 p3->Parent=p;
				 
				 p->Depth = (BYTE) (p3->Depth>=(p->Left)->Depth ? p3->Depth+1 : (p->Left)->Depth+1);
				 p2->Depth = (BYTE) (p->Depth>=(p2->Right)->Depth ? p->Depth+1 : (p2->Right)->Depth+1);
				 p=p2;
			 }
			 else
			 {
				 p3->Parent=Parent;
				 if(Parent!=NULL)
				 {
					 if(Parent->Right==p)
						 Parent->Right=p3;
					 else
						 Parent->Left=p3;
				 }
				 else
					 Root=p3;
				 if(p3->Right==NULL)
					 p2->Left=NULL;
				 else
				 {
					 p2->Left=p3->Right;
					 (p3->Right)->Parent=p2;
				 }
				 if(p3->Left==NULL)
					 p->Right=NULL;
				 else
				 {
					 p->Right=p3->Left;
					 (p3->Left)->Parent=p;
				 }
				 p3->Right=p2;
				 p2->Parent=p3;
				 p3->Left=p;
				 p->Parent=p3;
				 
				 if(p2->Left==NULL)
					 p2->Depth = (BYTE) ((p2->Right)->Depth+1);
				 else
					 p2->Depth = (BYTE) ((p2->Right)->Depth>=(p2->Left)->Depth ? (p2->Right)->Depth+1 : (p2->Left)->Depth+1);
				 if(p->Right==NULL)
					 p->Depth = (BYTE) ((p->Left)->Depth+1);
				 else
					 p->Depth = (BYTE) ((p->Right)->Depth>=(p->Left)->Depth ? (p->Right)->Depth+1 : (p->Left)->Depth+1);
				 p3->Depth = (BYTE) (p2->Depth>=p->Depth ? p2->Depth+1 : p->Depth+1);
				 p=p3;
			 }
		 }
    }
  }
  
  if(p!=Root)
  {
	  if(p->Left==NULL)
		  LDepth=0;
	  else
		  LDepth=(p->Left)->Depth;
	  if(p->Right==NULL)
		  RDepth=0;
	  else
		  RDepth=(p->Right)->Depth;
	  
	  p->Depth = (BYTE)  ((LDepth>=RDepth) ? LDepth+1: RDepth+1);
	  
	  if(OldDepth==1 || OldDepth!=p->Depth)
		  AVProc((void *)(p->Parent));
  }
}

template <class ITEM_TYPE, class KEY_TYPE, class PMKEY_TYPE>
item_pointer IT_AVTree<ITEM_TYPE, KEY_TYPE, PMKEY_TYPE>::
Insert(ITEM_TYPE& a_Item)
{
	IT_AVTreeNode *p;
	IT_AVTreeNode *p2;
	bool ToLeft;
	
	p = new IT_AVTreeNode;
	if(p==NULL) return NULL;
	p->Item=a_Item;
	
	if(Root==NULL)
	{
		p->Left=NULL;
		p->Right=NULL;
		p->Parent=NULL;
		p->Depth=1; // AV
		Root=p;
		count=1;
		return p;
	}
	
	p2=Root;
	for (;;)
	{
		if(CompareFunction((p->Item).*PointMem, (p2->Item).*PointMem)<0)
			ToLeft=true;
		else
			ToLeft=false;
		
		if(ToLeft)
			if(p2->Left!=NULL)
				p2=p2->Left;
			else
				break;
			else
				if(p2->Right!=NULL)
					p2=p2->Right;
				else
					break;
	}
	
	if(ToLeft)
		p2->Left=p;
	else
		p2->Right=p;
	
	p->Left=NULL;
	p->Right=NULL;
	p->Parent=p2;
	count++;
	
	p->Depth=1;
	AVProc((void *)p->Parent);
	
	return p;
}

template <class ITEM_TYPE, class KEY_TYPE, class PMKEY_TYPE>
void * IT_AVTree<ITEM_TYPE, KEY_TYPE, PMKEY_TYPE>::
First()
{
	IT_AVTreeNode *p;
	
	if(Root==NULL) return NULL;
	p=Root;
	for (;;)
	{
		if(p->Left==NULL) return (void *)p;
		p=p->Left;
	}
}

template <class ITEM_TYPE, class KEY_TYPE, class PMKEY_TYPE>
void * IT_AVTree<ITEM_TYPE, KEY_TYPE, PMKEY_TYPE>::
Last()
{
	IT_AVTreeNode *p;
	
	if(Root==NULL) return NULL;
	p=Root;
	for(;;)
	{
		if(p->Right==NULL) return (void *)p;
		p=p->Right;
	}
}

template <class ITEM_TYPE, class KEY_TYPE, class PMKEY_TYPE>
void * IT_AVTree<ITEM_TYPE, KEY_TYPE, PMKEY_TYPE>::
Next(void *Pointer)
{
	IT_AVTreeNode *p;
	IT_AVTreeNode *p2;
	
	p=(IT_AVTreeNode *)Pointer;
	
	if(p==NULL) return NULL;
	
	if(p->Right!=NULL)
	{
		p=p->Right;
		while(p->Left!=NULL)
			p=p->Left;
		return (void *)p;
	}
	
	for (;;)
	{
		p2=p->Parent;
		if(p2==NULL) return NULL;
		if(p2->Left==p) return p2;
		p=p2;
	}
}

template <class ITEM_TYPE, class KEY_TYPE, class PMKEY_TYPE>
void * IT_AVTree<ITEM_TYPE, KEY_TYPE, PMKEY_TYPE>::
Prev(void *Pointer)
{
	IT_AVTreeNode *p;
	IT_AVTreeNode *p2;
	
	p=(IT_AVTreeNode *)Pointer;
	
	if(p==NULL) return NULL;
	
	if(p->Left!=NULL)
	{
		p=p->Left;
		while(p->Right!=NULL)
			p=p->Right;
		return (void *)p;
	}
	
	for (;;)
	{
		p2=p->Parent;
		if(p2==NULL) return NULL;
		if(p2->Right==p) return p2;
		p=p2;
	}
}

template <class ITEM_TYPE, class KEY_TYPE, class PMKEY_TYPE>
void * IT_AVTree<ITEM_TYPE, KEY_TYPE, PMKEY_TYPE>::
Find(KEY_TYPE& Key, bool bInexact)
{
	IT_AVTreeNode *p;
	IT_AVTreeNode *_p=NULL;
	
	p=Root;
	for (;;)
	{
		if(p==NULL) 
		{
			return (!bInexact)? NULL: _p;
		}
		
		if(CompareFunction((p->Item).*PointMem, Key)==0)
		{
		// ������� ����� ������ � ���������� ������
			_p = p;
			bool eq = true;
			while (p && eq)
			{
				p=(IT_AVTreeNode *)(Prev(p));
				
				if (p) 
				{
					eq = (CompareFunction((p->Item).*PointMem, Key)==0);
					if (eq)
					{
						_p=p;
					}
				}
			}
			return _p;
		}

		if(CompareFunction(Key, (p->Item).*PointMem)<0){
			p=p->Left;
		}
		else{
			_p = p;
			p=p->Right;
		}
	}
}

template <class ITEM_TYPE, class KEY_TYPE, class PMKEY_TYPE>
void * IT_AVTree<ITEM_TYPE, KEY_TYPE, PMKEY_TYPE>::
NextWithSameKey(void *Pointer)
{
	IT_AVTreeNode *p;
	IT_AVTreeNode *_p;
	
	p=(IT_AVTreeNode *)Pointer;
	
	if(p==NULL) return NULL;
	
	_p=p;
	p=(IT_AVTreeNode *)(Next(p));
	if(p==NULL) return NULL;
	if(CompareFunction((p->Item).*PointMem, (_p->Item).*PointMem)==0)
		return (void *)p;
	else
		return NULL;
}

template <class ITEM_TYPE, class KEY_TYPE, class PMKEY_TYPE>
void * IT_AVTree<ITEM_TYPE, KEY_TYPE, PMKEY_TYPE>::
PrevWithSameKey(void *Pointer)
{
	IT_AVTreeNode *p;
	IT_AVTreeNode *_p;
	
	p=(IT_AVTreeNode *)Pointer;
	
	if(p==NULL) return NULL;
	
	_p=p;
	p=(IT_AVTreeNode *)(Prev(p));
	if(p==NULL) return NULL;
	if(CompareFunction((p->Item).*PointMem, (_p->Item).*PointMem)==0)
		return (void *)p;
	else
		return NULL;
}


template <class ITEM_TYPE, class KEY_TYPE, class PMKEY_TYPE>
bool IT_AVTree<ITEM_TYPE, KEY_TYPE, PMKEY_TYPE>::
CopyTo(void * Pointer, ITEM_TYPE& a_Item)
{
	if(Pointer==NULL) return false;
	a_Item=((IT_AVTreeNode *)Pointer)->Item;
	return true;
}

template <class ITEM_TYPE, class KEY_TYPE, class PMKEY_TYPE>
bool IT_AVTree<ITEM_TYPE, KEY_TYPE, PMKEY_TYPE>::
GetDepth(void *Pointer, int *Depth) // ����� ������� ��������
{
	if(Pointer==NULL) return false;
	*Depth=((IT_AVTreeNode *)Pointer)->Depth;
	return true;
}





// �������� ������� ������ �� ������
template <class ITEM_TYPE, class KEY_TYPE, class PMKEY_TYPE>
item_pointer IT_AVTree<ITEM_TYPE, KEY_TYPE, PMKEY_TYPE>::
Replace(item_pointer Pointer, ITEM_TYPE_REF Item) 
{
	if (Pointer!=NULL)
	{
		if (!Remove (Pointer)) return NULL; 
	}
	return Insert(Item);
}


template <class ITEM_TYPE, class KEY_TYPE, class PMKEY_TYPE>
bool IT_AVTree<ITEM_TYPE, KEY_TYPE, PMKEY_TYPE>::
Remove(void *Pointer)
{
	IT_AVTreeNode *p;
	IT_AVTreeNode *p2;
	IT_AVTreeNode *Parent;
	IT_AVTreeNode *pr1;
	IT_AVTreeNode *lt1;
	IT_AVTreeNode *rt1;
	IT_AVTreeNode *pr2;
	IT_AVTreeNode *lt2;
	IT_AVTreeNode *rt2;
	BYTE Depth;
	
	p=(IT_AVTreeNode *)Pointer;
	
	if(p==NULL) return false;
	
	if(p==Root)
	{
		if(p->Right==NULL && p->Left==NULL)
		{
			Root=NULL;
			count=0;
			delete p;
			return true;
		}
		
		if(p->Right==NULL)
		{
			Root=p->Left;
			Root->Parent=NULL;
			count--;
			delete p;
			return true;
		}
		if(p->Left==NULL)
		{
			Root=p->Right;
			Root->Parent=NULL;
			count--;
			delete p;
			return true;
		}
	}
	else
	{
		Parent=p->Parent;
		if(p->Right==NULL && p->Left==NULL)
		{
			if(Parent->Left==p){
				Parent->Left=NULL;
			}
			else{
				Parent->Right=NULL;
			}
			count--;
			delete p;
			AVProc((void *)Parent);
			return true;
		}
		
		if(p->Right==NULL)
		{
			if(Parent->Left==p){
				Parent->Left=p->Left;
			}
			else{
				Parent->Right=p->Left;
			}
			
			(p->Left)->Parent=Parent;
			count--;
			delete p;
			AVProc((void *)Parent);
			return true;
		}
		if(p->Left==NULL)
		{
			if(Parent->Left==p){
				Parent->Left=p->Right;
			}
			else{
				Parent->Right=p->Right;
			}
			
			(p->Right)->Parent=Parent;
			count--;
			delete p;
			AVProc((void *)Parent);
			return true;
		}
	}
	
	// � ��������� ������� ���� ��� �������.
	// ������� ��������� ������� �������� ��������� ,
	// ���������� ����� �� � ������ � �������  ������� (��������
	// �� ���������, �.�. � ��� ����� ���� ��� ���������� �� ��������).
	if((p->Right)->Depth>=(p->Left)->Depth)
	{
		p2=p->Right;
		while(p2->Left!=NULL)
			p2=p2->Left;
	}
	else
	{
		p2=p->Left;
		while(p2->Right!=NULL)
			p2=p2->Right;
	}
	
	// ����� ������� � ������
	pr1=p->Parent;
	if(p2->Parent==p)
		pr2=p2;
	else
		pr2=p2->Parent;
	if(p->Left!=p2)
		lt1=p->Left;
	else
		lt1=p;
	if(p->Right!=p2)
		rt1=p->Right;
	else
		rt1=p;
	lt2=p2->Left;
	rt2=p2->Right;
	
	p2->Parent=pr1;
	if(pr1==NULL)
		Root=p2;
	else
	{
		if(pr1->Left==p)
			pr1->Left=p2;
		else
			pr1->Right=p2;
	}
	p->Parent=pr2;
	if(pr2->Left==p2){
		pr2->Left=p;
	}
	else{
		pr2->Right=p;
	}
	p2->Left=lt1;
	if(lt1!=NULL) lt1->Parent=p2;
	p->Left=lt2;
	if(lt2!=NULL) lt2->Parent=p;
	p2->Right=rt1;
	if(rt1!=NULL) rt1->Parent=p2;
	p->Right=rt2;
	if(rt2!=NULL) rt2->Parent=p;
	Depth=p2->Depth;
	p2->Depth=p->Depth;
	p->Depth=Depth;
	
	return Remove((void *)p);
}

template <class ITEM_TYPE, class KEY_TYPE, class PMKEY_TYPE>
bool IT_AVTree<ITEM_TYPE, KEY_TYPE, PMKEY_TYPE>::RemoveAll()
{
	IT_AVTreeNode *p;
	IT_AVTreeNode *p2;
	
	p=Root;
	
	while(p!=NULL)
	{
		if(p->Left!=NULL)
			p=p->Left;
		else if(p->Right!=NULL)
			p=p->Right;
		else
		{
			p2=p;
			p=p->Parent;
			if(p!=NULL)
			{
				if(p->Left==p2)
					p->Left=NULL;
				else
					p->Right=NULL;
			}
			
			delete p2;
		}
	}
	
	Root=NULL;
	count=0;
	
	return true;
}  
//______________________________________________________________________________
//                                                                            []
// ������������� ������ � �������� �������������, �� �������� ��������			[]
// �������������� ����� ������ �� ������.													[]
// �������������� �������������� ������� �� 4+16*(sizeof(ITEM_TYPE)) ����.		[]
// ������� bool (*OutFunc)(BYTE *OutBlock) ���������� ���� ������					[]
// �� ����������. ���������� false ��� ������ ������.									[]
// ������ ������ ��������� ���� �� ���� �������. (���� ������ �����, �� ��		[]
// ����� ��� ������ ���-�� ����������, ������� ������������ ���� ���� ��������[]
//																										[]
template <class ITEM_TYPE, class KEY_TYPE, class PMKEY_TYPE>
bool IT_AVTree<ITEM_TYPE, KEY_TYPE, PMKEY_TYPE>::
ConvertTreeToBinaryData(bool (*OutFunc)(BYTE *OutBlock, int NumInBlock))
{
	BYTE *BinaryBlock;
	IT_AVTreeNode *CurNode;
	int NumInBlock;
	
	if(IsEmpty())
		return false;
	
	size_t item_size = sizeof(ITEM_TYPE);
	BinaryBlock = new BYTE [item_size*16+4];
	memset (BinaryBlock, 0, item_size*16+4);
	if(BinaryBlock==NULL)
		return false;
	
	CurNode=Root;
	NumInBlock=0;
	
	if(!ConvertNodeToBinaryData(OutFunc, BinaryBlock, &CurNode, &NumInBlock))
	{
		delete[] BinaryBlock;
		return false;
	}
	
	if(NumInBlock!=0)
		if(!(*OutFunc)(BinaryBlock, NumInBlock)) // �������� ����������� ����
			return false;
		
	delete[] BinaryBlock;
		
	return true;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// ���������� �������� �������������� �� ��������� ������������� � ������.		[]
// �������������� �������������� ������� �� 4+16*(sizeof(ITEM_TYPE)) ����.		[]
// ������� bool (*InFunc)(ITEM_TYPE *InBlock) ��������� ���� ������				[]
// ��� �������������� � ������. ���������� false ��� ������ ������.				[]
//																										[]
template <class ITEM_TYPE, class KEY_TYPE, class PMKEY_TYPE>
bool IT_AVTree<ITEM_TYPE, KEY_TYPE, PMKEY_TYPE>::
ConvertBinaryDataToTree(bool (*InFunc)(BYTE *InBlock))
{
	BYTE *BinaryBlock;
	BYTE Depth;
	IT_AVTreeNode *CurNode;
	int NumInBlock;
	
	if(!RemoveAll())                       // �������� ������
		return false;
	
	BinaryBlock = new BYTE [sizeof(ITEM_TYPE)*16+4];
	memset (BinaryBlock, 0, sizeof(ITEM_TYPE)*16+4);
	if(BinaryBlock==NULL)
		return false;
	NumInBlock=0;
	
	if(!(*InFunc)(BinaryBlock))
	{
		delete[] BinaryBlock;
		return false;
	}
	
	CurNode=new IT_AVTreeNode;
	if(CurNode==NULL)
	{
		delete[] BinaryBlock;
		return false;
	}
	CurNode->Parent=NULL;
	count++;
	Root=CurNode;
	
	if(!ConvertBinaryDataToNode(InFunc, BinaryBlock, &CurNode, &NumInBlock,
		&Depth))
	{
		delete[] BinaryBlock;
		return false;
	}
	
	delete[] BinaryBlock;
	
	return true;
}
//____________________________________________________________________________[]





/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` END OF FILE																					[]
[]                                                                            []
[]____________________________________________________________________________[]
*/
