/* ************************************************************************
> File Name:     skiplist.h
> Author:        程序员Carl
> 微信公众号:    代码随想录
> Created Time:  Sun Dec  2 19:04:26 2018
> Description:   
 ************************************************************************/

#include <iostream> 
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <mutex>
#include <fstream>

#define STORE_FILE "store/dumpFile"

std::mutex mtx;     // mutex for critical section
std::string delimiter = ":";

<<<<<<< HEAD
//Class template to      - 结点类
=======
//Class template to implement node
>>>>>>> cdd2eb16fef9efae838d79e179eedeee41a5c595
template<typename K, typename V> 
class Node {

public:
    
    Node() {} 

    Node(K k, V v, int); 

    ~Node();

    K get_key() const;

    V get_value() const;

    void set_value(V);
    
<<<<<<< HEAD

    Node<K, V> **forward;
    
    //这是一个数组，存储当前结点，在上面每一层的next结点。
    //比如:key为1的结点，在level=1层的next结点为key为2的结点，所以key为1的结点的forward[1] = key=2的node指针


/*
level 4:                            2:B
level 3:                            2:B
level 2:                            2:B                   4:D                6:F
level 1:               1:A          2:B                   4:D        5:E     6:F
level 0:               1:A          2:B         3:C       4:D        5:E     6:F
*/



=======
    // Linear array to hold pointers to next node of different level
    Node<K, V> **forward;
>>>>>>> cdd2eb16fef9efae838d79e179eedeee41a5c595

    int node_level;

private:
    K key;
    V value;
};

template<typename K, typename V> 
Node<K, V>::Node(const K k, const V v, int level) {
    this->key = k;
    this->value = v;
    this->node_level = level; 

    // level + 1, because array index is from 0 - level
    this->forward = new Node<K, V>*[level+1];
    
<<<<<<< HEAD
	// 初始化用0填充
=======
	// Fill forward array with 0(NULL) 
>>>>>>> cdd2eb16fef9efae838d79e179eedeee41a5c595
    memset(this->forward, 0, sizeof(Node<K, V>*)*(level+1));
};

template<typename K, typename V> 
Node<K, V>::~Node() {
    delete []forward;
};

template<typename K, typename V> 
K Node<K, V>::get_key() const {
    return key;
};

template<typename K, typename V> 
V Node<K, V>::get_value() const {
    return value;
};
<<<<<<< HEAD

=======
>>>>>>> cdd2eb16fef9efae838d79e179eedeee41a5c595
template<typename K, typename V> 
void Node<K, V>::set_value(V value) {
    this->value=value;
};

<<<<<<< HEAD

// Class template for Skip list - 跳表类
=======
// Class template for Skip list
>>>>>>> cdd2eb16fef9efae838d79e179eedeee41a5c595
template <typename K, typename V> 
class SkipList {

public: 
    SkipList(int);
    ~SkipList();
    int get_random_level();
    Node<K, V>* create_node(K, V, int);
    int insert_element(K, V);
    void display_list();
    bool search_element(K);
    void delete_element(K);
    void dump_file();
    void load_file();
    int size();

private:
    void get_key_value_from_string(const std::string& str, std::string* key, std::string* value);
    bool is_valid_string(const std::string& str);

private:    
<<<<<<< HEAD
    // 跳表最大高度
    int _max_level;

    // 当前高度
    int _skip_list_level;

    // 头结点指针
    Node<K, V> *_header; 

    // 文件操作
    std::ofstream _file_writer;
    std::ifstream _file_reader;

    // 跳表当前的元素数量
    int _element_count;
};

// 创建节点
=======
    // Maximum level of the skip list 
    int _max_level;

    // current level of skip list 
    int _skip_list_level;

    // pointer to header node 
    Node<K, V> *_header;

    // file operator
    std::ofstream _file_writer;
    std::ifstream _file_reader;

    // skiplist current element count
    int _element_count;
};

// create new node 
>>>>>>> cdd2eb16fef9efae838d79e179eedeee41a5c595
template<typename K, typename V>
Node<K, V>* SkipList<K, V>::create_node(const K k, const V v, int level) {
    Node<K, V> *n = new Node<K, V>(k, v, level);
    return n;
}

// Insert given key and value in skip list 
<<<<<<< HEAD
// return 1 means element exists  - 1 代表元素存在
// return 0 means insert successfully - 0 代表插入成功
=======
// return 1 means element exists  
// return 0 means insert successfully
>>>>>>> cdd2eb16fef9efae838d79e179eedeee41a5c595
/* 
                           +------------+
                           |  insert 50 |
                           +------------+
level 4     +-->1+                                                      100
                 |
                 |                      insert +----+
level 3         1+-------->10+---------------> | 50 |          70       100
                                               |    |
                                               |    |
level 2         1          10         30       | 50 |          70       100
                                               |    |
                                               |    |
level 1         1    4     10         30       | 50 |          70       100
                                               |    |
                                               |    |
level 0         1    4   9 10         30   40  | 50 |  60      70       100
                                               +----+

*/
<<<<<<< HEAD

//插入元素
=======
>>>>>>> cdd2eb16fef9efae838d79e179eedeee41a5c595
template<typename K, typename V>
int SkipList<K, V>::insert_element(const K key, const V value) {
    
    mtx.lock();
<<<<<<< HEAD
    Node<K, V> *current = this->_header;//先拿到头结点
    //TEST
    // 创建数组update并进行初始化
    // update is array which put node that the node->forward[i] should be operated later
    //update 为结点指针数组
    Node<K, V> *update[_max_level+1];
    memset(update, 0, sizeof(Node<K, V>*)*(_max_level+1));  

    // 从跳表左上角开始进行查找
    for(int i = _skip_list_level; i >= 0; i--) {
        //如果当前节点的forward数组不为空，即在当前层，存在当前结点，并且，存在next结点。
        //此循环成立条件如下:
        //除了上面说的那个条件，同时还要求，当前结点的key小于我们要查找的key,小于则继续往后面走。
        while(current->forward[i] != NULL && current->forward[i]->get_key() < key) {
            current = current->forward[i];//继续往后面走
        }
        //每一层记录一个结点，这个结点的作用是？
        //
        update[i] = current;
    }

    //到达第0层，并且当前的forward指针指向第一个大于待插入节点的节点。
    current = current->forward[0];

    // 存在即修改
    // 如果当前结点的key值和待插入节点的key相等，则说明待插入节点值存在，修改该节点的值，这里并没有进行修改。
=======
    Node<K, V> *current = this->_header;

    // create update array and initialize it 
    // update is array which put node that the node->forward[i] should be operated later
    Node<K, V> *update[_max_level+1];
    memset(update, 0, sizeof(Node<K, V>*)*(_max_level+1));  

    // start form highest level of skip list 
    for(int i = _skip_list_level; i >= 0; i--) {
        while(current->forward[i] != NULL && current->forward[i]->get_key() < key) {
            current = current->forward[i]; 
        }
        update[i] = current;
    }

    // reached level 0 and forward pointer to right node, which is desired to insert key.
    current = current->forward[0];

    // if current node have key equal to searched key, we get it
>>>>>>> cdd2eb16fef9efae838d79e179eedeee41a5c595
    if (current != NULL && current->get_key() == key) {
        std::cout << "key: " << key << ", exists" << std::endl;
        mtx.unlock();
        return 1;
    }

<<<<<<< HEAD
    //如果current结点为null，这就意味着要将该元素应该插入到最后
    //如果current的key值和待插入的key不等，代表我们应该在update[0]和current之间插入该节点。
    if (current == NULL || current->get_key() != key ) {
        
        // 为该节点计算出一个随机层次
        int random_level = get_random_level();

        // 如果随机出来的层数大于当前的
=======
    // if current is NULL that means we have reached to end of the level 
    // if current's key is not equal to key that means we have to insert node between update[0] and current node 
    if (current == NULL || current->get_key() != key ) {
        
        // Generate a random level for node
        int random_level = get_random_level();

>>>>>>> cdd2eb16fef9efae838d79e179eedeee41a5c595
        // If random level is greater thar skip list's current level, initialize update value with pointer to header
        if (random_level > _skip_list_level) {
            for (int i = _skip_list_level+1; i < random_level+1; i++) {
                update[i] = _header;
            }
            _skip_list_level = random_level;
        }

<<<<<<< HEAD
        // 创建新节点
        Node<K, V>* inserted_node = create_node(key, value, random_level);
        
        // 插入结点
=======
        // create new node with random level generated 
        Node<K, V>* inserted_node = create_node(key, value, random_level);
        
        // insert node 
>>>>>>> cdd2eb16fef9efae838d79e179eedeee41a5c595
        for (int i = 0; i <= random_level; i++) {
            inserted_node->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = inserted_node;
        }
        std::cout << "Successfully inserted key:" << key << ", value:" << value << std::endl;
        _element_count ++;
    }
    mtx.unlock();
    return 0;
}

// Display skip list 
template<typename K, typename V> 
void SkipList<K, V>::display_list() {

    std::cout << "\n*****Skip List*****"<<"\n"; 
    for (int i = 0; i <= _skip_list_level; i++) {
        Node<K, V> *node = this->_header->forward[i]; 
        std::cout << "Level " << i << ": ";
        while (node != NULL) {
            std::cout << node->get_key() << ":" << node->get_value() << ";";
            node = node->forward[i];
        }
        std::cout << std::endl;
    }
}

// Dump data in memory to file 
template<typename K, typename V> 
void SkipList<K, V>::dump_file() {

    std::cout << "dump_file-----------------" << std::endl;
    _file_writer.open(STORE_FILE);
    Node<K, V> *node = this->_header->forward[0]; 

    while (node != NULL) {
        _file_writer << node->get_key() << ":" << node->get_value() << "\n";
        std::cout << node->get_key() << ":" << node->get_value() << ";\n";
        node = node->forward[0];
    }

    _file_writer.flush();
    _file_writer.close();
    return ;
}

<<<<<<< HEAD
// Load data from disk - 从磁盘中加载数据
=======
// Load data from disk
>>>>>>> cdd2eb16fef9efae838d79e179eedeee41a5c595
template<typename K, typename V> 
void SkipList<K, V>::load_file() {

    _file_reader.open(STORE_FILE);
    std::cout << "load_file-----------------" << std::endl;
    std::string line;
    std::string* key = new std::string();
    std::string* value = new std::string();
    while (getline(_file_reader, line)) {
        get_key_value_from_string(line, key, value);
        if (key->empty() || value->empty()) {
            continue;
        }
        insert_element(*key, *value);
        std::cout << "key:" << *key << "value:" << *value << std::endl;
    }
    _file_reader.close();
}

<<<<<<< HEAD
// 当前跳表元素数量
=======
// Get current SkipList size 
>>>>>>> cdd2eb16fef9efae838d79e179eedeee41a5c595
template<typename K, typename V> 
int SkipList<K, V>::size() { 
    return _element_count;
}

template<typename K, typename V>
void SkipList<K, V>::get_key_value_from_string(const std::string& str, std::string* key, std::string* value) {

    if(!is_valid_string(str)) {
        return;
    }
    *key = str.substr(0, str.find(delimiter));
    *value = str.substr(str.find(delimiter)+1, str.length());
}

template<typename K, typename V>
bool SkipList<K, V>::is_valid_string(const std::string& str) {

    if (str.empty()) {
        return false;
    }
    if (str.find(delimiter) == std::string::npos) {
        return false;
    }
    return true;
}

// Delete element from skip list 
template<typename K, typename V> 
void SkipList<K, V>::delete_element(K key) {

    mtx.lock();
    Node<K, V> *current = this->_header; 
    Node<K, V> *update[_max_level+1];
    memset(update, 0, sizeof(Node<K, V>*)*(_max_level+1));

    // start from highest level of skip list
    for (int i = _skip_list_level; i >= 0; i--) {
        while (current->forward[i] !=NULL && current->forward[i]->get_key() < key) {
            current = current->forward[i];
        }
        update[i] = current;
    }

    current = current->forward[0];
    if (current != NULL && current->get_key() == key) {
       
        // start for lowest level and delete the current node of each level
        for (int i = 0; i <= _skip_list_level; i++) {

            // if at level i, next node is not target node, break the loop.
            if (update[i]->forward[i] != current) 
                break;

            update[i]->forward[i] = current->forward[i];
        }

        // Remove levels which have no elements
        while (_skip_list_level > 0 && _header->forward[_skip_list_level] == 0) {
            _skip_list_level --; 
        }

        std::cout << "Successfully deleted key "<< key << std::endl;
        _element_count --;
    }
    mtx.unlock();
    return;
}

// Search for element in skip list 
/*
                           +------------+
                           |  select 60 |
                           +------------+
level 4     +-->1+                                                      100
                 |
                 |
level 3         1+-------->10+------------------>50+           70       100
                                                   |
                                                   |
level 2         1          10         30         50|           70       100
                                                   |
                                                   |
level 1         1    4     10         30         50|           70       100
                                                   |
                                                   |
level 0         1    4   9 10         30   40    50+-->60      70       100
*/
template<typename K, typename V> 
bool SkipList<K, V>::search_element(K key) {

    std::cout << "search_element-----------------" << std::endl;
    Node<K, V> *current = _header;

<<<<<<< HEAD
    // 从左上角开始寻找
=======
    // start from highest level of skip list
>>>>>>> cdd2eb16fef9efae838d79e179eedeee41a5c595
    for (int i = _skip_list_level; i >= 0; i--) {
        while (current->forward[i] && current->forward[i]->get_key() < key) {
            current = current->forward[i];
        }
    }

    //reached level 0 and advance pointer to right node, which we search
    current = current->forward[0];

    // if current node have key equal to searched key, we get it
    if (current and current->get_key() == key) {
        std::cout << "Found key: " << key << ", value: " << current->get_value() << std::endl;
        return true;
    }

    std::cout << "Not Found Key:" << key << std::endl;
    return false;
}

<<<<<<< HEAD
// int 有参构造
=======
// construct skip list
>>>>>>> cdd2eb16fef9efae838d79e179eedeee41a5c595
template<typename K, typename V> 
SkipList<K, V>::SkipList(int max_level) {

    this->_max_level = max_level;
    this->_skip_list_level = 0;
    this->_element_count = 0;

<<<<<<< HEAD
    //创建头节点 并将K与V初始化为NULL
=======
    // create header node and initialize key and value to null
>>>>>>> cdd2eb16fef9efae838d79e179eedeee41a5c595
    K k;
    V v;
    this->_header = new Node<K, V>(k, v, _max_level);
};

<<<<<<< HEAD
//析构
=======
>>>>>>> cdd2eb16fef9efae838d79e179eedeee41a5c595
template<typename K, typename V> 
SkipList<K, V>::~SkipList() {

    if (_file_writer.is_open()) {
        _file_writer.close();
    }
    if (_file_reader.is_open()) {
        _file_reader.close();
    }
    delete _header;
}

<<<<<<< HEAD

=======
>>>>>>> cdd2eb16fef9efae838d79e179eedeee41a5c595
template<typename K, typename V>
int SkipList<K, V>::get_random_level(){

    int k = 1;
    while (rand() % 2) {
        k++;
    }
    k = (k < _max_level) ? k : _max_level;
    return k;
};
// vim: et tw=100 ts=4 sw=4 cc=120
