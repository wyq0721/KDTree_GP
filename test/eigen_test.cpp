#include <iostream>
#include <stdio.h>
#include <cmath>

// 告诉C++编译器该头文件内用C编译器解释
extern "C"{
#include "../kdtree.h"
}

////绝对路径，这是我电脑的缘故，在你电脑上应该可以直接include
//#include </usr/local/Cellar/eigen/3.3.5/include/eigen3/Eigen/Core>
//#include </usr/local/Cellar/eigen/3.3.5/include/eigen3/Eigen/Dense>

#include </usr/include/eigen3/Eigen/Core>
#include </usr/include/eigen3/Eigen/Dense>

using namespace std;


const int N = 10;
typedef Eigen::Matrix<double, 3, N> scan;

// 输出显示
static void kdtree_knn_dump(struct kdtree *tree)
{
        int i;
        struct knn_list *p = tree->knn_list_head.next;
        while (p != &tree->knn_list_head) {
                putchar('(');
                for (i = 0; i < tree->dim; i++) {
                        if (i == tree->dim - 1) {
                                printf("%.2lf) Distance:%lf\n", p->node->coord[i], sqrt(p->distance));
                        } else {
                                printf("%.2lf, ", p->node->coord[i]);
                        }
                }
                p = p->next;
        }
}

int main () {
    cout << "Eigen Test:" << endl;
    scan gp;
    gp << 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
          11, 12, 33, 44, 64, 53, 7, 14, 49, 5,
          12, 0, 8, 98, 7, 43, 9, 83, 8, 2;
   
    // cout << gp.block<2,1>(0,0);
    
   	  
    // 初始化kdtree为2维
    int dim = 2;
    struct kdtree *tree = kdtree_init(dim);
    if (tree == NULL) {
            exit(-1);
    }

	for (int i = 0; i < N; ++i)
	{
		double sample[] = {gp(0,i), gp(1,i)}; 
	    kdtree_insert(tree, sample);/*void kdtree_insert(struct kdtree *tree, double *coord)*/
    } 


    // 创建kdtree， 虽然名字是rebuild， 里面的函数就是build
    kdtree_rebuild(tree);

    // 可视化
    // kdtree_dump(tree);

    //搜索目标点附近的临近点
    int k = 3;
    double target[] = { -1, -5 };
    kdtree_knn_search(tree, target, k);

    // 输出结果
    printf("Find %d nearest neighbors of target(", k);
    for (int i = 0; i < dim; i++) {
            if (i == dim - 1) {
                    printf("%.2lf):\n", target[i]);
            } else {
                    printf("%.2lf, ", target[i]);
            }
    }
    kdtree_knn_dump(tree);

    // 回收内存
    kdtree_destroy(tree);

	return 0;
}