def floyd(graph):
    distances = [row[:] for row in graph]
    V = len(distances)

    for k in range(V):
        for i in range(V):
            for j in range(V):
                distances[i][j] = min(distances[i][j], distances[i][k] + distances[k][j])
    
    return distances

graph = [
    [0, 2, 3, 4], 
    [2, 0, 3, float('inf')],
    [3, 3, 0, float('inf')],
    [4, float('inf'), float('inf'), 0]
]

def main():
    out = floyd(graph)
    for i in out:
        for j in i:
            print(j, end=' ')
        print()

if __name__ == '__main__':
    main()