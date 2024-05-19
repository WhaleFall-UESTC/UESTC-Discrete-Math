import heapq;

def dijkstra(graph, start):
    distances = {node : float('inf') for node in graph}
    distances[start] = 0
    priority_q = [(0, start)]

    while priority_q:
        cur_distance, cur_node = heapq.heappop(priority_q)

        if (cur_distance > distances[cur_node]):
            continue;

        for neighbor, weight in graph[cur_node].items():
            # print(weight, neighbor)
            new_distance = cur_distance + weight
            if new_distance < distances[neighbor]:
                distances[neighbor] = new_distance
                heapq.heappush(priority_q, (new_distance, neighbor))

    return distances


graph = {
    'a' : { 'b': 2, 'c': 3}, 
    'b' : { 'a': 2, 'c': 1, 'd': 2}, 
    'c' : { 'a': 2, 'd': 1 }, 
    'd' : { 'b': 2, 'c': 1, 'e': 1, 'f': 2 }, 
    'e' : { 'd': 1, 'f': 1 }, 
    'f' : { 'd': 2, 'e': 1 }
}

def main():  
    froms = [[n, dijkstra(graph, n)] for n in graph.keys()]
    for i in froms:
        for j in i[1].keys():
            print(i[0], "->", j, ":", i[1][j])
        print()
        

if __name__ == '__main__':
    main()