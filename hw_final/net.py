import numpy as np
from scipy.sparse import csr_matrix, coo_matrix, lil_matrix
from sklearn.metrics import roc_auc_score
import random
import csv

filename = 'ca-HepTh.txt'
testname = 'test.txt'
nr_nodes = 0
s = 0.85
samples = []
nmap = {}
cnt_nodes = 0


# 输出一个 csr_matrix
def print_matrix(m):
    print(m.toarray())


# 将 node 的值映射到 0 - nr_nodes
def node_map(node):
    node = int(node)
    global nmap, cnt_nodes

    if node in nmap:
        return nmap[node]
    else:
        nmap[node] = cnt_nodes
        cnt_nodes += 1
        return cnt_nodes - 1


# 根据行列的 List 创建一个稀疏矩阵
def sparse_martix(rows, cols):
    data = np.ones(len(rows))
    res = coo_matrix((data, (rows, cols)), shape=(nr_nodes, nr_nodes)).tocsr()
    return res;


# 从文件中初始化一个稀疏矩阵，并抽出矩阵的 1/5，创建真实标签矩阵
def init_matrix(filename):
    rows = []
    cols = []
    eval_rows = []
    eval_cols = []
    global nr_nodes
    global samples
    global node_map

    with open(filename, 'r') as f:
        reader = csv.reader(f, delimiter = '\t')
        while True:
            row = next(reader)
            info = str(row)
            if '#' not in info:
                rows.append(node_map(row[0]))
                cols.append(node_map(row[1]))
                break
            index = info.find('Nodes:')
            if index != -1:
                end = info.find('Edges:')
                nr_nodes = int(info[index + 6: end].replace(' ', ''))
                continue

        for row in reader:
            r = node_map(row[0])
            l = node_map(row[1])

            if (random.randint(1, 5) == 1):
                eval_rows.append(r)
                eval_cols.append(l)
                samples.append([r, l])
            else:
                rows.append(r)
                cols.append(l)

    data = sparse_martix(rows, cols)
    eval = sparse_martix(eval_rows, eval_cols)
    return data, eval


# 社会资本指数打分
def score_sci(matrix, s):
    res = s * matrix
    matrix_power = matrix
    s_power = s

    for i in range(2, 10):
        matrix_power = matrix_power.dot(matrix)
        s_power *= s
        res += s_power * matrix_power

    return res


# 获取与真实标签矩阵对应的分数矩阵
def get_eval(graph, samples):
    res = lil_matrix(graph.shape, dtype=graph.dtype)
    for index in samples:
        row, col = int(index[0]), int(index[1])
        res[row, col] = graph[row, col]
    return res.tocsr()


def main():
    print("Initializing graph and selecting samples...", end=' ')
    graph, eval_labels = init_matrix(filename)
    print("Done")

    print("Calculating scores...", end=' ')
    score_graph = score_sci(graph, s)
    print("Done")

    print("Seek eval_score table...", end=' ')
    eval_score = get_eval(score_graph, samples)
    print('Done')

    print("Calculating AUC...", end=' ')
    auc = roc_auc_score(eval_labels.toarray().flatten(), eval_score.toarray().flatten())
    print('Done')
    print('AUC:', auc)


if __name__ == '__main__':
    main()