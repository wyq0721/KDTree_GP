#include <iostream>
#include </usr/include/eigen3/Eigen/Core>
#include </usr/include/eigen3/Eigen/Dense>

// 告诉C++编译器该头文件内用C编译器解释
extern "C"{
#include "../kdtree.h"
}



using namespace std;

const int N = 10;
typedef Eigen::Matrix<double, 3, N> scan;

int main () {
    cout << "Eigen Test:" << endl;
    scan gp;
    gp << 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
          11, 12, 33, 44, 64, 53, 7, 14, 49, 5,
          12, 0, 8, 98, 7, 43, 9, 83, 8, 2;
   	  
    // 初始化kdtree为2维
    int dim = 2;
    struct kdtree *tree = kdtree_init(dim);
    if (tree == NULL) {
            return -1;
    }

	for (int i = 0; i < N; ++i)
	{
		double sample[] = {gp(0,i), gp(1,i)}; 
	    kdtree_insert(tree, sample);
    } 


    // 创建kdtree， 虽然名字是rebuild， 里面的函数就是build
    kdtree_build(tree);

    // kd-tree可视化
     kdtree_dump(tree);

    //搜索目标点附近的临近点
    int k = 3;
    double target[] = { -1, -5 };
    kdtree_knn_search(tree, target, k);

    // 输出knn结果
    cout << "Find " << k << " nearest neighbors of target[" << target[0] << "," << target[1] << "]:" << endl;
    kdtree_knn_result(tree);

    // 回收内存
    kdtree_destroy(tree);

	return 0;
}