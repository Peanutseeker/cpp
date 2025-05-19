#include <iostream>
#include <string>
#include "MemoryRiver.hpp"

// 测试用的学生结构体
struct Student {
    int id;
    char name[64];
    double score;

    void display() const {
        std::cout << "ID: " << id << ", Name: " << name << ", Score: " << score << std::endl;
    }
};

// 测试用的图书结构体
struct Book {
    int id;
    char title[128];
    char author[64];
    float price;

    void display() const {
        std::cout << "Book ID: " << id << ", Title: " << title 
                  << ", Author: " << author << ", Price: " << price << std::endl;
    }
};

// 测试基本功能
void testBasicFunctions() {
    std::cout << "\n=== Testing Basic Functions ===\n";
    
    // 初始化
    MemoryRiver<Student, 3> studentRiver("students.dat");
    studentRiver.initialise();
    
    // 写入元信息
    int studentCount = 0;
    studentRiver.write_info(studentCount, 1);
    
    // 添加学生
    Student s1 = {1, "Alice", 95.5};
    Student s2 = {2, "Bob", 87.0};
    Student s3 = {3, "Charlie", 92.3};
    
    // 写入并记录位置
    int pos1 = studentRiver.write(s1);
    studentCount++;
    studentRiver.write_info(studentCount, 1);
    std::cout << "Student 1 written at position: " << pos1 << std::endl;
    
    int pos2 = studentRiver.write(s2);
    studentCount++;
    studentRiver.write_info(studentCount, 1);
    std::cout << "Student 2 written at position: " << pos2 << std::endl;
    
    int pos3 = studentRiver.write(s3);
    studentCount++;
    studentRiver.write_info(studentCount, 1);
    std::cout << "Student 3 written at position: " << pos3 << std::endl;
    
    // 读取学生信息
    Student readStudent;
    studentRiver.read(readStudent, pos2);
    std::cout << "Read student from position " << pos2 << ": ";
    readStudent.display();
    
    // 更新学生
    readStudent.score = 91.0;
    studentRiver.update(readStudent, pos2);
    std::cout << "Updated student at position " << pos2 << std::endl;
    
    // 重新读取验证更新
    Student updatedStudent;
    studentRiver.read(updatedStudent, pos2);
    std::cout << "Read updated student: ";
    updatedStudent.display();
    
    // 读取元信息
    int storedCount;
    studentRiver.get_info(storedCount, 1);
    std::cout << "Stored student count: " << storedCount << std::endl;
}

// 测试另一种数据类型
void testDifferentDataType() {
    std::cout << "\n=== Testing Different Data Type ===\n";
    
    MemoryRiver<Book, 2> bookRiver("books.dat");
    bookRiver.initialise();
    
    Book b1 = {101, "The Great Gatsby", "F. Scott Fitzgerald", 12.99};
    Book b2 = {102, "To Kill a Mockingbird", "Harper Lee", 10.50};
    
    int pos1 = bookRiver.write(b1);
    int pos2 = bookRiver.write(b2);
    
    std::cout << "Book 1 written at position: " << pos1 << std::endl;
    std::cout << "Book 2 written at position: " << pos2 << std::endl;
    
    Book readBook;
    bookRiver.read(readBook, pos1);
    std::cout << "Read book from position " << pos1 << ": ";
    readBook.display();
    
    // 更新信息
    readBook.price = 14.99;
    bookRiver.update(readBook, pos1);
    
    // 验证更新
    bookRiver.read(readBook, pos1);
    std::cout << "Read updated book: ";
    readBook.display();
}

// 测试多次操作的持久性
void testPersistence() {
    std::cout << "\n=== Testing Persistence ===\n";
    
    // 打开已存在的文件
    MemoryRiver<Student, 3> studentRiver("students.dat");
    
    // 读取元信息
    int count;
    studentRiver.get_info(count, 1);
    std::cout << "Existing student count: " << count << std::endl;
    
    // 写入第四个学生
    Student s4 = {4, "David", 88.7};
    int pos4 = studentRiver.write(s4);
    count++;
    studentRiver.write_info(count, 1);
    std::cout << "Student 4 written at position: " << pos4 << std::endl;
    
    // 读取前面写入的学生
    Student readStudent;
    studentRiver.read(readStudent, pos4);
    std::cout << "Read new student: ";
    readStudent.display();
}

int main() {
    testBasicFunctions();
    testDifferentDataType();
    testPersistence();
    
    std::cout << "\nAll tests completed!\n";
    return 0;
}