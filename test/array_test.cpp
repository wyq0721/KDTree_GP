#include <iostream>
#include <stdio.h>
#include <cmath>

// 告诉C++编译器该头文件内用C编译器解释
extern "C"{
#include "../kdtree.h"
}

using namespace std;

// 输出显示
static void kdtree_knn_dump(struct kdtree *tree)
{
        int i;
        struct knn_list *p = tree->knn_list_head.next;
        while (p != &tree->knn_list_head) {
                putchar('(');
                for (i = 0; i < tree->dim; i++) {
                        if (i == tree->dim - 1) {
                                // printf("%.2lf) Distance:%lf\n", p->node->coord[i], sqrt(p->distance));
                                //此处为新改动， 即从coord_index中得到返回的最近点在原数组中的索引（索引从0开始）
                                printf("%.2lf) Distance:%lf, Index: %ld\n", p->node->coord[i], sqrt(p->distance), p->node->coord_index);
                        } else {
                                printf("%.2lf, ", p->node->coord[i]);
                        }
                }
                p = p->next;
        }
}

int main(void)
{
        // 初始化kd-tree为2维
        int dim = 2;
        struct kdtree *tree = kdtree_init(dim);
        if (tree == NULL) {
          return -1;
        }

        // 往kd-tree插入平面点（x,y）
        double sample1[] = { 6.27, 5.50 };
        double sample2[] = { 1.24, -2.86 };
        double sample3[] = { 17.05, -12.79 };
        double sample4[] = { -6.88, -5.40 };
        double sample5[] = { -2.96, -0.50 };
        double sample6[] = { 7.75, -22.68 };
        double sample7[] = { 10.80, -5.03 };
        double sample8[] = { -4.60, -10.55 };
        double sample9[] = { -4.96, 12.61 };
        double sample10[] = { 1.75, 12.26 };

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
        kdtree_rebuild(tree);

        // 可视化
        kdtree_dump(tree);

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

