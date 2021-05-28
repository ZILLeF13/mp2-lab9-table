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
	int DataCount,Eff;
public:
	TTable();
	bool IsEmpty();
	virtual bool IsFull() const= 0;
	virtual bool Find(TKey key) = 0;
	virtual bool Insert(TRecord rec) = 0;
	virtual bool Delete(TKey key) = 0;
	virtual void Reset() = 0;
	virtual void GoNext() = 0;
	virtual bool IsEnd() = 0;
	virtual TRecord GetCurr() = 0;
	void Print();
	int GetEff()const ;
	int GetDataCount()const ;
	void CLiarEff();
};

TTable::TTable()
{
	DataCount = 0;
	Eff = 0;
}

bool TTable::IsEmpty()
{
	if (DataCount == 0)
		return true;
	else
		return false;
}

void TTable::Print()
{
	std::cout << "key   val" << std::endl;
	TRecord rec;
	for (Reset(); !IsEnd(); GoNext())
	{
		rec = this->GetCurr();
		std::cout <<  rec.key << "   " << rec.val << std::endl;
	}
}

int TTable::GetEff()const 
{
	return Eff ;
}

void TTable::CLiarEff()
{
	Eff = 0; 
}

int TTable::GetDataCount()const 
{
	return DataCount;
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
	TArrayTable(const TArrayTable& ta);
	~TArrayTable();
	bool IsFull()const override;
	TRecord& GetCurrRec();
	void Reset()override;
	void GoNext()override;
	bool IsEnd()override;
	int GetSize()const;
	TRecord GetCurr()override;

	//int GetDataCount();
};

TArrayTable::TArrayTable(int _size):TTable()
{
	size = _size;
	pRec = new TRecord[size];
	curr = -1;
}

TArrayTable::TArrayTable(const TArrayTable& ta)
{
	size = ta.size;
	curr = ta.curr;
	DataCount = ta.DataCount;
	pRec = new TRecord[size];
	for (Reset(); !IsEnd(); GoNext())
		pRec[curr] = ta.pRec[curr];
}

TArrayTable::~TArrayTable()
{
	delete[] pRec;
}

bool TArrayTable::IsFull()const
{
	if (DataCount == size)
		return true;
	else
		return false;
}

TRecord& TArrayTable::GetCurrRec()
{
	if (DataCount > 0)
		return pRec[curr];
	else
		throw 0; 
}

void TArrayTable::Reset()
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
		return true;
	else
		return false;
}

int TArrayTable::GetSize()const
{
	return size;
}

TRecord TArrayTable::GetCurr()
{
	return pRec[curr];
}

//********************************************************************************

class TScanTable : public TArrayTable
{
public:
	TScanTable(int _size) :TArrayTable(_size) {};
	TScanTable(const TScanTable& ts) {};
	bool Find(TKey k)override;
	bool Delete(TKey k)override;
	bool Insert(TRecord rec)override;
	void Print();
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

bool TScanTable::Insert(TRecord rec)  
{
	if (!Find(rec.key))
	{
		if (DataCount < size)
		{
			pRec[curr] = rec;
			DataCount++;
			Eff++;
			return true;
		}
	}
	return false;
}

void TScanTable::Print()
{
	std::cout << "key   val" << std::endl;
	TRecord rec;
	for (Reset(); !IsEnd(); GoNext())
	{
		rec = this->GetCurr();
		std::cout << rec.key << "   " << rec.val << std::endl;
	}
}

//********************************************************************************

class TSortTable :public TArrayTable
{
public:
	TSortTable(int _size) :TArrayTable(_size) {};
	TSortTable(const TArrayTable& ta) :TArrayTable(ta) { Sort(); }
	bool Find(TKey k)override;
	bool Insert(TRecord rec)override;
	bool Delete(TKey k)override;
	TSortTable& operator =(TArrayTable& ta); 
	void Sort();
	void Print();
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

TSortTable& TSortTable::operator=(TArrayTable& ta) 
{
	if (size != ta.GetSize())
	{
		delete[] pRec;
		size = ta.GetSize();
		pRec = new TRecord[size];
		DataCount = ta.GetDataCount();
		for (ta.Reset(); !ta.IsEnd(); ta.GoNext())
		{
			Eff++;
			pRec[curr] = ta.GetCurr();
			curr++;
		}
		Sort();
	}
	return *this;
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
					Eff++;
				}
}

void TSortTable::Print()
{
	std::cout << "key   val" << std::endl;
	TRecord rec;
	for (Reset(); !IsEnd(); GoNext())
	{
		rec = this->GetCurr();
		std::cout << rec.key << "   " << rec.val << std::endl;
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
	int n;
public:
	TTreeTable();
	~TTreeTable();
	bool Find(TKey k)override;
	bool Insert(TRecord rec)override;
    bool Delete(TKey k)override;
	void Reset() override;
	void GoNext() override;
	bool IsEnd() override;
	bool IsFull()const override;
	TRecord GetCurr()override;
	void Print();
};

TTreeTable::TTreeTable()
{
	pRoot = pCurr = pPrev = NULL;
	n = 0;
}

TTreeTable::~TTreeTable()
{
	while (!st.empty())
		st.pop();
	pCurr = pRoot;
	while (!st.empty())
	{
		pCurr = st.top();
		st.pop();
		if (pCurr->pLeft)
			st.push(pCurr->pLeft);
		else if (pCurr->pRight)
			st.push(pCurr->pRight);
		delete pCurr;
	}
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

bool TTreeTable::Insert(TRecord rec)
{
	TNode n;
	n.key = rec.key;
	n.val = rec.val;
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

void TTreeTable::Reset()
{
	while (!st.empty())
		st.pop();
	pCurr = pRoot;
	n = 0;
	if (pCurr) {
		while (pCurr->pLeft)
			pCurr = pCurr->pLeft;
		n++;
	}
}
void TTreeTable::GoNext()
{
	if (pCurr)
	{
		TNode* tmp = pCurr = pCurr->pRight;
		if (!st.empty())
			st.pop();
		while (tmp)
		{
			st.push(tmp);
			pCurr = tmp;
			tmp = tmp->pLeft;
		}
		if (!pCurr && !st.empty())
		{
			pCurr = st.top();
			st.pop();
		}
		n++;
	}
}
bool TTreeTable::IsEnd()
{
	return n == DataCount;
}

void TTreeTable::Print()
{
	std::cout << "key   val" << std::endl;
	for (Reset(); !IsEnd(); GoNext())
	{
		std::cout << pCurr->key << "   " <<pCurr->val<< std::endl;
	}
}

TRecord TTreeTable::GetCurr()
{
	TRecord rec;
	rec.key = pCurr->key;
	rec.val = pCurr->val;
	return rec;
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
	THashTable(const THashTable& th);

	bool Find(TKey k)override;
	bool Insert(TRecord rec)override;
	bool Delete(TKey k)override;
	void Reset()override;
	void GoNext()override;
	bool IsEnd()override;
	bool IsFull()const override;
	TRecord GetCurr()override;
	void Print();
};

THashTable::THashTable(int _MaxSize, int _Step)
{
	MaxSize = _MaxSize;
	Step = _Step;
	mas = new TRecord[MaxSize];
	for (int i=0; i < MaxSize; i++)
	{
		mas[i].key = Free;
	}
}

THashTable::THashTable(const THashTable& th)
{
	MaxSize = th.MaxSize;
	Step = th.Step;
	mas = new TRecord[MaxSize];
	for (int i=0; i < MaxSize; i++)
	{
		mas[i].key = th.mas[i].key;
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

bool THashTable::Delete(TKey k)
{
	if (Find(k))
	{
		mas[Curr].key = Del;
		DataCount--;
		Eff++;
		return true;
	}
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

void THashTable::Reset()
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
	return false;
}

void THashTable::Print()
{
	std::cout << "key   val" << std::endl;
	for (Reset(); !IsEnd(); GoNext())
	{
		std::cout << mas[Curr].key << "   " << mas[Curr].val << std::endl;
	}
}

bool THashTable::IsFull()const 
{
	if (MaxSize == DataCount)
		return true;
	return false;
}

TRecord THashTable::GetCurr()
{
	return mas[Curr];
}