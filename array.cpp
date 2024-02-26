#include <iostream>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iterator>

template<typename T>
class BaseArray {
protected:
    T* data;
    size_t size;

public:
    BaseArray(size_t size) : size(size) {
        data = new T[size];
    }

    virtual ~BaseArray() {
        delete[] data;
    }

    T& operator[](size_t index) {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    size_t getSize() const {
        return size;
    }

    virtual void print() const {
        for (size_t i = 0; i < size; ++i) {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }
};

template<typename T>
class ArrayOperations : public BaseArray<T> {
public:
    using BaseArray<T>::BaseArray;

    double computeMean() const {
        if (this->getSize() == 0) {
            throw std::logic_error("Array is empty");
        }
        T sum = std::accumulate(this->data, this->data + this->getSize(), static_cast<T>(0));
        return static_cast<double>(sum) / this->getSize();
    }

    void stack(const ArrayOperations<T>& other) {
        size_t newSize = this->getSize() + other.getSize();
        T* newData = new T[newSize];

        std::copy(this->data, this->data + this->getSize(), newData);
        std::copy(other.data, other.data + other.getSize(), newData + this->getSize());

        delete[] this->data;
        this->data = newData;
        this->size = newSize;
    }

    static ArrayOperations<T> concatenate(const ArrayOperations<T>& arr1, const ArrayOperations<T>& arr2) {
        ArrayOperations<T> result(arr1.getSize() + arr2.getSize());

        std::copy(arr1.data, arr1.data + arr1.getSize(), result.data);
        std::copy(arr2.data, arr2.data + arr2.getSize(), result.data + arr1.getSize());

        return result;
    }

    std::vector<T> flatten() const {
        return std::vector<T>(this->data, this->data + this->getSize());
    }

    void clip(const T& min_val, const T& max_val) {
        for (size_t i = 0; i < this->getSize(); ++i) {
            this->data[i] = std::min(std::max(this->data[i], min_val), max_val);
        }
    }
};

int main() {
    ArrayOperations<int> arr1(5);
    ArrayOperations<int> arr2(3);

    for (size_t i = 0; i < arr1.getSize(); ++i) {
        arr1[i] = i + 1;
    }

    for (size_t i = 0; i < arr2.getSize(); ++i) {
        arr2[i] = i + 6;
    }

    std::cout << "Array 1: ";
    arr1.print();
    std::cout << "Array 2: ";
    arr2.print();

    std::cout << "Mean of Array 1: " << arr1.computeMean() << std::endl;

    arr1.stack(arr2);
    std::cout << "Stacked Array: ";
    arr1.print();

    ArrayOperations<int> arr3 = ArrayOperations<int>::concatenate(arr1, arr2);
    std::cout << "Concatenated Array: ";
    arr3.print();

    std::vector<int> flattened = arr3.flatten();
    std::cout << "Flattened Array: ";
    for (const auto& elem : flattened) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    arr3.clip(2, 8);
    std::cout << "Clipped Array: ";
    arr3.print();

    return 0;
}
