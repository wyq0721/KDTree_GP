#include <iostream>

// 告诉C++编译器该头文件内用C编译器解释
extern "C"{
#include "../kdtree.h"
}

using namespace std;


int main(void)
{
        // 初始化kd-tree为2维
        int dim = 2;
        struct kdtree *tree = kdtree_init(dim);
        if (tree == NULL) {
          return -1;
        }

        // 往kd-tree插入平面点（x,y）
        double sample1[] = { 6.27, 5.50, 5 };
        double sample2[] = { 1.24, -2.86, 42 };
        double sample3[] = { 17.05, -12.79, 4 };
        double sample4[] = { -6.88, -5.40, 43 };
        double sample5[] = { -2.96, -0.50, 4 };
        double sample6[] = { 7.75, -22.68, 4.3 };
        double sample7[] = { 10.80, -5.03, 4 };
        double sample8[] = { -4.60, -10.55, 4 };
        double sample9[] = { -4.96, 12.61, 4 };
        double sample10[] = { 1.75, 12.26, 4 };

        kdtree_insert(tree, sample1);
        kdtree_insert(tree, sample2);
        kdtree_insert(tree, sample3);
        kdtree_insert(tree, sample4);
        kdtree_insert(tree, sample5);
        kdtree_insert(tree, sample6);
        kdtree_insert(tree, sample7);
        kdtree_insert(tree, sample8);
        kdtree_insert(tree, sample9);
        kdtree_insert(tree, sample10);


        // 创建kd-tree
        kdtree_build(tree);

        // kd-tree可视化
        kdtree_dump(tree);

        //搜索目标点附近的临近点
        int k = 3;
        double target[] = { -1, -5, 5 };
        kdtree_knn_search(tree, target, k);

        // 输出knn结果
        cout << "Find " << k << " nearest neighbors of target[" << target[0] << "," << target[1] << "]:" << endl;
        kdtree_knn_result(tree);

        // 回收内存
        kdtree_destroy(tree);

        return 0;
}

