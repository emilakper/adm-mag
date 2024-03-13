#include <iostream>
#include <locale.h>

std::exception wrong_index("Index out of array size!");

// ����� ������������� �������, �������������� �� ������� ������.
class AdjArray {
public:
	AdjArray() = default;
	// �������� ������� ������� size, ������������ �������������� ����������
	AdjArray(const size_t& size) {
		size_ = size;
		data_ = new double[size_];

		for (int i = 0; i < size_; i++) {
			data_[i] = 0.0;
		}
	}
	// �������� ������� ������� size, � ���������� ������� value
	AdjArray(const size_t& size, const double& value) {
		size_ = size;
		data_ = new double[size_];

		for (int i = 0; i < size_; i++) {
			data_[i] = value;
		}
	}
	~AdjArray() {
		delete[] data_;
	}

	// �������� ������ ������� ����� ��� ������������ ������. ��������������� �������� �����.
	AdjArray(const AdjArray& other) {
		size_ = other.size_;
		data_ = new double[size_];
		for (int i = 0; i < size_; i++) {
			data_[i] = other.data_[i];
		}
	}

	// ������ � �������� �������
	double& operator[](const ptrdiff_t& index) {
		CheckIndex(index);
		return data_[index];
	}

	// ������� ������ �������� � ������ ��� ����� �������� �� 0 �� size - 1
	void Insert(const ptrdiff_t& index, const double& value) {
		CheckIndex(index);
		AdjArray copy(*this);
		size_ += 1;
		delete[] data_;
		data_ = new double[size_];
		for (int i = 0; i < size_; i++) {
			if (i < index) {
				data_[i] = copy.data_[i];
			}
			else if (i == index) {
				data_[i] = value;
			}
			else {
				data_[i] = copy.data_[i - 1];
			}
		}
	}

	// �������� ������ ��������
	void Remove(const ptrdiff_t& index) {
		CheckIndex(index);
		AdjArray copy(*this);
		size_ -= 1;
		delete[] data_;
		data_ = new double[size_];
		for (int i = 0; i < size_; i++) {
			if (i < index) {
				data_[i] = copy.data_[i];
			}
			else {
				data_[i] = copy.data_[i + 1];
			}
		}
	}

	// ���������� ������ �������� � ����� �������
	void PushBack(const double& value) {
		AdjArray copy(*this);
		size_ += 1;
		delete[] data_;
		data_ = new double[size_];
		for (int i = 0; i < size_ - 1; i++) {
			data_[i] = copy.data_[i];
		}
		data_[size_ - 1] = value;
	}
	// �������� ���������� ��������
	void PopBack() {
		this->Remove(this->size_ - 1);
	}
	// ���������� ������ �������� � ������ �������
	void PushFront(const double& value) {
		this->Insert(0, value);
	}
	// �������� ������� �������� �������
	void PopFront() {
		this->Remove(0);
	}
	void PrintArr() {
		std::cout << "[";
		for (int i = 0; i < size_; i++) {
			if (i == size_ - 1) {
				std::cout << data_[i] << "]" << std::endl;
			}
			else {
				std::cout << data_[i] << ", ";
			}
		}
	}


private:
	double* data_ = nullptr;
	size_t size_ = 0;

	void CheckIndex(const ptrdiff_t& index) {
		if (index >= size_ || index < 0) {
			throw wrong_index;
		}
	}
};

// ����� �������� �������
class List {
public:
	List() = default;
	~List() {
		while (size != 0) {
			this->PopFront();
		}
	}

	double& operator[](const ptrdiff_t& index) {
		Node* current = this->head;
		for (int i = 0; i < index; i++) {
			current = current->next_;
		}
		return current->data_;
	}

	void PushBack(double data) {
		if (head == nullptr) {
			head = new Node(data);
			size += 1;
		}
		else {
			Node* current = this->head;
			while (current->next_ != nullptr) {
				current = current->next_;
			}
			current->next_ = new Node(data);
			size += 1;
		}
	}
	
	void Insert(const ptrdiff_t& index, double data) {
		Node* current = this->head;
		for (int i = 0; i < index - 1; i++) {
			current = current->next_;
		}
		Node* save = current->next_;
		current->next_ = new Node(data, save);
		size += 1;
	}

	void PushFront(double data) {
		Node* save = this->head;
		head = new Node(data, save);
		size += 1;
	}

	void PopFront() {
		Node* save = this->head->next_;
		delete this->head;

		head = save;
		size -= 1;
	}
	void Remove(const ptrdiff_t& index) {
		if (size == 0) { return; }
		if (index == 0) {
			this->PopFront();
		}
		else {
			Node* previous = this->head;
			for (int i = 0; i < index - 1; i++) {
				previous = previous->next_;
			}

			Node* toDelete = previous->next_;
			previous->next_ = toDelete->next_;

			delete toDelete;
			size -= 1;
		}
	}

	void PopBack() {
		this->Remove(size - 1);
	}

	void PrintList() {
		std::cout << "[";
		for (int i = 0; i < size; i++) {
			if (i == size - 1) {
				std::cout << (*this)[i] << "]" << std::endl;
			}
			else {
				std::cout << (*this)[i] << ", ";
			}
		}
	}



private:
	class Node {
	public:
		Node* next_ = nullptr;
		double data_ = 0;

		Node() = default;

		Node(double data = 0, Node* next = nullptr) {
			data_ = data;
			next_ = next;
		}
	};

	Node* head = nullptr;
	size_t size = 0;
};


int main() {
	setlocale(LC_ALL, "ru");

	std::cout << "          ������ �� ������� ������" << std::endl;
	std::cout << "1) �������� �������: ";
	AdjArray arr(3);
	arr[0] = 1;
	arr[1] = 2;
	arr[2] = 4;
	arr.PrintArr();

	std::cout << "2) ���������� �������� � ������: ";
	arr.PushFront(0);
	arr.PrintArr();

	std::cout << "3) ���������� ������ �������� ��� �������� 3: ";
	arr.Insert(3, 3);
	arr.PrintArr();

	std::cout << "4) ���������� �������� � ����� �������: ";
	arr.PushBack(5);
	arr.PrintArr();

	std::cout << "5) �������� ���������� �������� �������: ";
	arr.PopBack();
	arr.PrintArr();

	std::cout << "6) �������� �������� ��� �������� 3: ";
	arr.Remove(3);
	arr.PrintArr();

	std::cout << "7) �������� ������� �������� �������: ";
	arr.PopFront();
	arr.PrintArr();

	std::cout << "������ ��������� �������: ";
	std::cout << &arr[0] << " " << &arr[1] << " " << &arr[2] << " - ���� ������" << std::endl;

	std::cout << std::endl;
	std::cout << "=====================================================================================================" << std::endl;
	std::cout << std::endl;

	std::cout << "          ������ �� ������� ������" << std::endl;

	std::cout << "1) �������� �������: ";
	List list;
	list.PushBack(1);
	list.PushBack(2);
	list.PushBack(4);
	list.PrintList();

	std::cout << "2) ���������� �������� � ������: ";
	list.PushFront(0);
	list.PrintList();

	std::cout << "3) ���������� ������ �������� ��� �������� 3: ";
	list.Insert(3, 3);
	list.PrintList();

	std::cout << "4) �������� �������� ��� �������� 3: ";
	list.Remove(3);
	list.PrintList();

	std::cout << "5) �������� ������� �������� �������: ";
	list.PopFront();
	list.PrintList();

	std::cout << "������ ���������: ";
	std::cout << &list[0] << " " << &list[1] << " " << &list[2] << " - �������� ����� � ������ �� ������" << std::endl;
}