#pragma once
#include<iostream>
using namespace std;
#include<assert.h>


/*������iteraotr��STL��һ����Ҫ��ɲ���,ͨ��iterator���Ժܷ���Ĵ洢�����е�Ԫ��.
STLΪÿ��������д��һ����Ϊ������ָ����ࡪ������������������ʵ�Ƕ�һ��ָ��İ�װ,
����ģ��ָ��ʵ��һЩ���õķ���,��++,--,!=,==,*,->�ȡ�
ͨ����Щ���������ҵ���ǰԪ�ػ��Ǳ��Ԫ��. vector��STL�����бȽ������һ��,
��Ϊvector�е�ÿ��Ԫ�ض���������,�������Լ�ʵ��vector��ʱ�������ָ����棬List�ռ䲻������
Ҫ��ֱ��ʹ��++,--,!=,==,*,->�ȷ���������ʹ��ָ�룬�ͱ���ʹ�õ�����*/


//~~~~~~~~~~~~~~~~~~~~~~~~~~~STLģ��ʵ�ֿ�List����ͷ����˫��ѭ������~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//��㹹��
template<class T>
struct ListNode//��������
{
	ListNode(const T& x = T())
		: _prev(0)
		, _next(0)
		, _value(x)
	{}

	ListNode<T>* _prev;
	ListNode<T>* _next;
	T _value;
};


//����������ʵ��,��ʵ���Ƕ�ָ��İ�װ
template<class T, class Ref, class Ptr>//ģ������б��ﶨ��ĵ���������
struct ListIterator//�����������
{
	typedef ListIterator<T, Ref, Ptr> Self;//����������������<T, Ref, Ptr>ʱ������������Ϊ self��������
	typedef ListIterator<T, T&, T*> Iterator;//������ͱ��<T, T&, T*>���൱�ڶ�ģ������б����������ʵ�����ˣ�������������ΪIterator
	typedef ListIterator<const T, const T&, const T*> ConstItrator;
	typedef T ValueType;
	typedef Ref Reference;
	typedef Ptr Pointer;
	typedef ListNode<T>* Node;//���������ָ��ΪNode
	typedef size_t SizeType;

	Node _node;

	ListIterator(Node x)
		:_node(x)
	{}

	ListIterator()
		:_node(NULL)
	{}

	ListIterator(const Iterator& x)
		:_node(x._node)
	{}

	bool operator==(const Iterator& x)
	{
		return _node == x._node;

	}

	bool operator!=(const Iterator& x)
	{
		return _node != x._node;

	}

	Reference operator*()//�����õõ���ǰ�����������ָ��_node��ָ�����_valueֵ
	{
		return (*_node)._value;

	}

	Pointer operator->()//->�õ���ǰ�����������ָ��_node��ָ�����_valueֵ��ָ��
	{
		return &((*_node)._value);

	}

	//ǰ��++
	Self& operator++()//���ص������������
	{
		_node = _node->_next;
		return *this;
	}

	//����++
	Self operator++(int)//���ص�������Ķ���
	{
		Self temp(*this);
		_node = _node->_next;
		return temp;

	}

	//ǰ��--
	Self& operator--()
	{
		_node = _node->_prev;
		return *this;

	}

	//����--
	Self operator--(int)
	{
		Self temp(*this);
		_node = _node->_prev;
		return temp;
	}

};



//������
template<class T>
class List
{
public:
	typedef T ValueType;
	typedef ValueType* Pointer;
	typedef const ValueType* ConstPointer;
	typedef ValueType& Reference;
	typedef const ValueType& ConstReference;
	typedef ListNode<T> Node;
	typedef Node* LinkType;
	typedef ListIterator<T, T&, T*> Iterator;
	typedef ListIterator<const T, const T& ,const T*> ConstIterator;
	typedef size_t SizeType;

	//����
	List()
		:_head(BuyNewNode())
	{
		_head->_next = _head;
		_head->_prev = _head;

	}

	//��������
	List(const List<T>& l)
	{
		
		_head = BuyNewNode();
		_head->_next = _head;
		_head->_prev = _head;

		LinkType tmp = l._head->_next;
		while(tmp != l._head)
		{
			PushBack(tmp->_value);
			tmp = tmp->_next;
		}

	}



	//��ֵ���������
	List& operator=(const List& l)
	{
		if(_head != l._head)	//�жϲ����Լ����Լ���ֵ
		{
			if(true != Empty())	//���*this�ǿգ����*this
			{
				Clear();
			}

			LinkType tmp = l._head->_next;
			while(tmp != l._head)
			{
				PushBack(tmp->_value);
				tmp = tmp->_next;
			}

		}

		return *this;

	}


	
	//����
	~List()
	{
		Clear();
		Iterator it = End();
		delete it._node;
	}

	Iterator Begin()
	{
		return (Iterator)(_head->_next);
	}
	ConstIterator Begin()const
	{
		return (ConstIterator)(_head->_next);
	}

	Iterator End()
	{
		return (Iterator)_head;
	}
	ConstIterator End()const
	{
		return (ConstIterator)_head;
	}

	bool Empty()const
	{
		return _head == _head->_next;
	}

	SizeType Size()const
	{	
		SizeType count = 0;
		Iterator it = Begin();
		while(it != End())
		{
			it++;
			count++;
		}
		return count;

	}

	Reference Front()
	{
		return *(Begin());//��Begin()���صĵ����������_nodeָ�����_valueȡ����
	}
	ConstReference Front()const
	{
		return *(Begin());
	}
	Reference Back()
	{
		return *(--End());
	}
	ConstReference Back()const
	{
		return *(--End());
	}

	//����λ�ò���
	Iterator Insert(Iterator pos, const T& x)
	{
		assert(pos._node);//��������������ָ������ڵ��ָ�벻��Ϊ�գ���������Ϊ�գ�

		Iterator tmp ;
		tmp._node= BuyNewNode(x);
		tmp._node->_next = pos._node;
		tmp._node->_prev = pos._node->_prev;
		pos._node->_prev = tmp._node;
		tmp._node->_prev->_next = tmp._node;

		return tmp;

	}

	//ͷ��
	void PushFront(const T& x)  
	{
		Insert(Begin(),x);

	}
	//β��
	void PushBack(const T& x)
	{
		Insert(End(),x);
	}

	//����λ��ɾ��
	Iterator Erase(Iterator pos)
	{
		//��������������ָ������ڵ��ָ�벻��Ϊ�գ���������Ϊ�գ���Ҳ����ָ��ͷ���
		assert(pos._node && pos._node != _head);

		pos._node->_prev->_next = pos._node->_next;
		pos._node->_next->_prev = pos._node->_prev;

		LinkType tmp = pos._node->_next;
		delete pos._node;
		pos._node = NULL;

		return (Iterator)tmp;
	}

	//ͷɾ
	void PopFront()
	{
		Erase(Begin());
	}

	//βɾ
	void PopBack()
	{
		Erase(--End());//pos��_node����ָ��ͷ���
	}

	//���
	void Clear()
	{
		Iterator it = Begin();
		Iterator temp = it;
		while(temp != End())
		{
			it++;
			delete temp._node;
			temp = it;
		}
		it._node->_next = _head;
		it._node->_prev = _head;

	}


	//��ӡ
	void Show()
	{
		if(true != Empty())
		{
			Iterator it = Begin();
			while(it != End())
			{
				cout<<*it<<"->";
				it++;
			}
			cout<<"end"<<endl;
		}

	}



protected:
	LinkType BuyNewNode(const T& data = T())
	{
		LinkType temp = new Node(data);
		return temp;
	}
protected:
	LinkType _head;

};



int main()
{
	//List<int> l1;
	List<int> l2;
	l2.PushBack(1);
	l2.PushBack(2);
	l2.PushBack(3);
	l2.PushBack(4);
	l2.PopBack();
	l2.PopBack();
	List<int> l1(l2);
	//l1 = l2;
	//l2.Clear();
	l1.Show();
	//if(true != l2.Empty())
	//{
	//	cout<<l2.Size()<<endl;
	//}

	//l2.PushFront(1);
	//l2.PushFront(2);
	//l2.PushFront(3);
	//l2.PushFront(4);
	//l2.PopFront();
	//l2.PopFront();

	//l2.Show();

	//system("pause");
	return 0;
}




