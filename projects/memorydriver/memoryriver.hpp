#ifndef BPT_MEMORYRIVER_HPP
#define BPT_MEMORYRIVER_HPP

#include <fstream>

using std::string;
using std::fstream;
using std::ifstream;
using std::ofstream;

template<class T, int info_len = 2>
class MemoryRiver {
private:
    /* your code here */
    fstream file;
    string file_name;
    int sizeofT = sizeof(T);
public:
    MemoryRiver() = default;

    MemoryRiver(const string& file_name) : file_name(file_name) {}

    void initialise(string FN = "") {
        if (FN != "") file_name = FN;
        file.open(file_name, std::ios::out);
        int tmp = 0;
        for (int i = 0; i < info_len; ++i)
            file.write(reinterpret_cast<char *>(&tmp), sizeof(int));
        file.close();
    }
    //提醒：用二进制读写文件！！
    //输出流是程序向文件中写入数据，用的是seekp
    //输入流是文件向程序传递数据，用的是seekg（记忆：get）
    //读出第n个int的值赋给tmp，1_base
    void get_info(int &tmp, int n) {
        if (n > info_len) return;
        /* your code here */
        file.open(file_name,std::ios::binary|std::ios::in);
        if(!file.is_open()) return;
        file.seekg((n-1)*sizeof(int),std::ios::beg);
        file.read(reinterpret_cast<char*>(&tmp),sizeof(int));
        file.close();
    }

    //将tmp写入第n个int的位置，1_base
    void write_info(int tmp, int n) {
        if (n > info_len) return;
        /* your code here */
        file.open(file_name,std::ios::binary|std::ios::in|std::ios::out);
        if(!file.is_open()) return;
        file.seekp((n-1)*sizeof(int),std::ios::beg);
        file.write(reinterpret_cast<char*>(&tmp), sizeof(tmp));
        file.close();
    }

    //在文件合适位置写入类对象t，并返回写入的位置索引index
    //位置索引意味着当输入正确的位置索引index，在以下三个函数中都能顺利的找到目标对象进行操作
    //位置索引index可以取为对象写入的起始位置
    int write(T &t) {
        /* your code here */
        file.open(file_name,std::ios::binary|std::ios::in|std::ios::out);
        if(!file.is_open()) return -1;
        file.seekp(0,std::ios::end);
        std::streampos t_pos=file.tellp();
        file.write(reinterpret_cast<char*>(&t),sizeofT);
        file.close();
        return int(t_pos);
    }

    //用t的值更新位置索引index对应的对象，保证调用的index都是由write函数产生
    void update(T &t, const int index) {
        /* your code here */
        file.open(file_name,std::ios::binary|std::ios::in|std::ios::out);
        if(!file.is_open()) return;
        file.seekp(index,std::ios::beg);
        file.write(reinterpret_cast<char*>(&t),sizeofT);
        file.close();
    }

    //读出位置索引index对应的T对象的值并赋值给t，保证调用的index都是由write函数产生
    void read(T &t, const int index) {
        /* your code here */
        file.open(file_name,std::ios::binary|std::ios::in|std::ios::out);
        if(!file.is_open()) return;
        file.seekg(index,std::ios::beg);
        file.read(reinterpret_cast<char*>(&t),sizeofT);
        file.close();
    }

    //删除位置索引index对应的对象(不涉及空间回收时，可忽略此函数)，保证调用的index都是由write函数产生
    void Delete(int index) {
        /* your code here */
    }
};


#endif //BPT_MEMORYRIVER_HPP复制