#pragma once
#include <iostream>
#include <stack>


typedef int TKey;
typedef int TVal;

struct TRecord
{
	TKey key;
	TVal val;
};

class TTable
{
protected:
	int DataCount=0;
	int Eff=0;
public:
	bool IsEmpty()
	{
		if (DataCount == 0)
			return false;
		else
			return true;
	}
	virtual bool IsFull() = 0;
	virtual bool Find(TKey key) = 0;
	virtual bool Insert(TRecord rec) = 0;
	virtual bool Delete(TKey key) = 0;
	virtual void Resert() = 0;
	virtual void GoNext() = 0;
	virtual bool IsEnd() = 0;
	virtual TRecord GetCurr() = 0;
	void Print();
	int GetF();
	void CLiarF();
};

void TTable::Print()
{
	for (Resert(); IsEnd(); GoNext())
	{

	}
}

int TTable::GetF() //узнать где сейчас
{
	return ;
}

void TTable::CLiarF()
{
	DataCount = 0; ///?????????
}

//********************************************************************************

class TArrayTable :public TTable
{
protected:
	TRecord* pRec;
	int size;
	int curr;
public:
	TArrayTable(int _size = 100);
	~TArrayTable();
	//копирование????
	bool IsFull();
	TRecord& GetCurrRec();
	void Resert();
	void GoNext();
	bool IsEnd();
};

TArrayTable::TArrayTable(int _size):TTable()
{
	size = _size;
	pRec = new TRecord[size];
	curr = -1;
}

TArrayTable::~TArrayTable()
{

}

bool TArrayTable::IsFull()
{
	if (DataCount == size)
		return true;
	else
		return false;
}

TRecord& TArrayTable::GetCurrRec()
{
	if (DataCount>0)
	return pRec[curr];     //исключение?+
}

void TArrayTable::Resert()
{
	curr = 0;
}

void TArrayTable::GoNext()
{
	curr++;
}

bool TArrayTable::IsEnd()
{
	if (curr == DataCount)
		return 1;
}

//********************************************************************************

class TScanTable : public TArrayTable
{
public:
	TScanTable(int _size):TArrayTable(_size){}
	bool Find(TKey k);
	bool Delete(TKey k);  
	void Insert(TKey k);
};

bool TScanTable::Find(TKey k)
{
	bool flag = false;
	for (int i = 0; i < DataCount; i++)
	{
		Eff++;
		if (pRec[i].key == k)
		{
			flag = true;
			curr = i;
			break;
		}
	}
	if (!flag)
		curr = DataCount;
	return flag;
}

bool TScanTable::Delete(TKey k)
{
	if (Find(k))
	{
		pRec[curr] = pRec[DataCount - 1];
		DataCount--;
		Eff++;
		return true;
	}
	return false;
}

void TScanTable::Insert(TKey k)  //добавить TRecord
{
	if (!Find(k))
	{
		if (DataCount < size)
		{

		}
	}
}

//********************************************************************************

class TSortTable :public TScanTable
{
public:
	TSortTable(int _size) :TScanTable(_size) {};
	//~TSortTable();
	bool Find(TKey k);
	bool Insert(TRecord rec);
	bool Delete(TKey k);
	void operator =(const TSortTable& st); //Scan?
	void Sort();
};


bool TSortTable::Find(TKey k)
{
	bool flag = false;
	int first = 0, last = DataCount - 1, mid;
	while (first <= last)
	{
		Eff++;
		mid = (first + last) / 2;
		if (pRec[mid].key == k)
		{
			curr = mid;
			flag = true;
			break;
		}
		else
			if (pRec[mid].key > k)
				last = mid - 1;
			else
				first = mid + 1;
	}
	if (flag == false)
		curr == first;
	return flag;
}

bool TSortTable::Insert(TRecord  rec)
{
	if (Find(rec.key))
		return false;
	else
	{
		for (int i = DataCount - 1; i >= curr; i--)
		{
			pRec[i + 1] = pRec[i];
			Eff++;
		}
		pRec[curr] = rec;
		DataCount++;
		return true;
	}
}

bool TSortTable::Delete(TKey k)
{
	if (Find(k))
	{
		for (int i = curr; i < DataCount; i++)
		{
			pRec[i] = pRec[i + 1];
		}
		DataCount--;
		return true;
	}
	return false;
}

void TSortTable::operator=(const TSortTable& st) 
{
	if (size != st.size)
	{
		delete[] pRec;
		size = st.size;
		pRec = new TRecord[size];
		DataCount = st.DataCount;
	}
	for (int i = 0; i < DataCount; i++)
	{
		pRec[i] = st.pRec[i];
	}
}

void TSortTable::Sort()
{
	if (DataCount > 1)
		for (int i = 0; i < DataCount; i++)
			for (int j = i; i < DataCount; j++)
				if (pRec[i].key < pRec[j].key)
				{
					TRecord tmp = pRec[i];
					pRec[i] = pRec[j];
					pRec[j] = tmp;
				}
}

//********************************************************************************

struct TNode
{
	TNode* pLeft, * pRight;
	TKey key;
	TVal val;
};

//********************************************************************************

class TTreeTable :public TTable
{
protected:
	TNode* pRoot, * pCurr, * pPrev;
	std::stack<TNode*> st;
public:
	TTreeTable();
	~TTreeTable();
	bool Find(TKey k);
	bool Insert(TNode n);
    bool Delete(TKey k);
};

TTreeTable::TTreeTable()
{
	pRoot = pCurr = pPrev = NULL;
}

TTreeTable::~TTreeTable()
{

}

bool TTreeTable::Find(TKey k)
{
	pCurr = pRoot;
	pPrev = NULL;
	while (pCurr)
	{
		Eff++;
		if (pCurr->key == k)
			break;
		else
		{
			pPrev = pCurr;
			if (pCurr->key < k)
				pCurr = pCurr->pRight;
			else
				pCurr = pCurr->pLeft;
		}
	}
	if (pCurr)
		return true;
	else
	{
		pCurr = pPrev;
		return false;
	}
}

bool TTreeTable::Insert(TNode n)
{
	if (Find(n.key))
		return false;
	Eff++;
	DataCount++;
	TNode* tmp = new TNode(n);
	if (pRoot == NULL)
		pRoot = tmp;
	else
	{
		if (pCurr->key > n.key)
			pCurr->pLeft = tmp;
		else
			pCurr->pRight = tmp;
	}
}

bool TTreeTable::Delete(TKey k)
{
	if (Find(k))
	{
		if (!pCurr->pLeft && !pCurr->pRight)
			if (pPrev->pLeft == pCurr)
				pPrev->pLeft = NULL;
			else
				pPrev->pRight = NULL;
		delete pCurr;
		return true;
	}
	else
		if (pCurr->pLeft && !pCurr->pRight)
		{
			if (pPrev->pLeft == pCurr)
				pPrev->pLeft = pCurr->pLeft;
			else
				pPrev->pRight = pCurr->pLeft;
			delete pCurr;
			return true;
		}
		else
			if (!pCurr->pLeft && pCurr->pRight)
			{
				if (pPrev->pRight == pCurr)
					pPrev->pRight = pCurr->pRight;
				else
					pPrev->pLeft = pCurr->pRight;
				delete pCurr;
				return true;
			}
			else
			{
				if (pCurr->pLeft && pCurr->pRight)
				{
					TNode* tmp = pCurr->pLeft;
					pPrev = pCurr;
					while (tmp->pRight != NULL)
					{
						pPrev = tmp;
						tmp = tmp->pRight;
					}
					pCurr->val = tmp->val;
					pCurr->key = tmp->key;
					if (pPrev->pLeft = tmp)
						pPrev->pLeft = tmp->pLeft;
					else
						pPrev->pRight = tmp->pLeft;
					delete tmp;
					DataCount--;
					delete pCurr;
					return true;
				}
			}
	return false;
}

//********************************************************************************

class THashTable : public TTable
{
protected:
	int MaxSize, Curr, DelPos, Step;
	TRecord* mas;
	const int Free = -1;
	const int Del = -2;
	int HashFunc(TKey k)
	{
		return k & MaxSize;
	}
public:
	THashTable(int _MaxSize, int _Step);
	bool Find(TKey k);
	bool Insert(TRecord rec);
	bool Delete(TKey k);
	void Resert();
	void GoNext();
	bool IsEnd();
};

THashTable::THashTable(int _MaxSize, int _Step)
{
	MaxSize = _MaxSize;
	Step = _Step;
	mas = new TRecord[MaxSize];
	for (int i; i < MaxSize; i++)
	{
		mas[i].key = Free;
	}
}

bool THashTable::Find(TKey k)
{
	DelPos = -1;
	Curr = HashFunc(k);
	for (int i = 0; i < MaxSize; i++)
	{
		Eff++;
		if (mas[Curr].key == k)
			return true;
		else
			if (mas[Curr].key == Del && DelPos == -1)
				DelPos = Curr;
			else
				if (mas[Curr].key == Free)
					break;
		Curr = (Curr + Step) % MaxSize;
	}
	if (DelPos != -1)
		Curr = DelPos;
	return false;
}


bool THashTable::Insert(TRecord rec)
{
	if (!Find(rec.key))
	{
		mas[Curr] = rec;
		DataCount++;
		return true;
	}
	else
		return false;
}

void THashTable::Resert()
{
	for (Curr = 0; Curr < MaxSize; Curr++)
		if (mas[Curr].key != Del && mas[Curr].key != Free)
			break;
}

void THashTable::GoNext()
{
	for (Curr++; Curr < MaxSize; Curr++)
		if (mas[Curr].key != Del && mas[Curr].key != Free)
			break;
}

bool THashTable::IsEnd()
{
	if (Curr == MaxSize)
		return true;
}