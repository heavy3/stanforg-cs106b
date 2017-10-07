// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own, along with
// comments on every function and on complex code sections.
// TODO: write comment header for this file; remove this comment

#include "Trailblazer.h"
#include "queue.h"
#include "priorityqueue.h"
#include "set.h"

using namespace std;

static const double SUFFICIENT_DIFFERENCE = 0.2;

Path breadthFirstSearch(const RoadGraph& graph, RoadNode* start, RoadNode* end) {
    /* TODO: Delete the following lines and implement this function! */
    Queue<Path> queue;

    Path path;
    path.add(start);
    queue.enqueue(path);

    Set<RoadNode*> visited;

    while (!queue.isEmpty() && !visited.contains(end)) {
        Path currentPath = queue.dequeue();
        RoadNode* nodeEnd = currentPath.get(currentPath.size() - 1);

        if (!visited.contains(nodeEnd)) {
            visited.add(nodeEnd);
            nodeEnd->setColor(Color::GREEN);

            if (nodeEnd == end)
                return currentPath;

            Set<RoadNode*> neighbors = graph.neighborsOf(nodeEnd);
            neighbors = neighbors.removeAll(visited);

            for (RoadNode* node: neighbors) {
                node->setColor(Color::YELLOW);
                Path newPath;
                newPath.addAll(currentPath);
                newPath.add(node);
                queue.enqueue(newPath);
            }
        }
    }

    // cant find path
    return {};
}

Path dijkstrasAlgorithm(const RoadGraph& graph, RoadNode* start, RoadNode* end) {
    /* TODO: Delete the following lines and implement this function! */
    PriorityQueue<pair<Path, double>> pathQueue;

    Path path;
    path.add(start);
    pathQueue.enqueue(make_pair(path, 0.0), 0.0);

    Set<RoadNode*> visited;

    while (!pathQueue.isEmpty() && !visited.contains(end)) {
        pair<Path, double> pathPair = pathQueue.dequeue();
        Path currentPath = pathPair.first;
        double currentCost = pathPair.second;

        RoadNode* nodeEnd = currentPath.get(currentPath.size() - 1);

        if (!visited.contains(nodeEnd)) {
            visited.add(nodeEnd);
            nodeEnd->setColor(Color::GREEN);

            if (nodeEnd == end)
                return currentPath;

            Set<RoadNode*> neighbors = graph.neighborsOf(nodeEnd);
            neighbors = neighbors.removeAll(visited);

            for (RoadNode* node: neighbors) {
                node->setColor(Color::YELLOW);

                RoadEdge* edge = graph.edgeBetween(nodeEnd, node);
                double cost = currentCost + edge->cost();

                Path newPath;
                newPath.addAll(currentPath);
                newPath.add(node);

                pathQueue.enqueue(make_pair(newPath, cost), cost);
            }
        }
    }

    // cant find path
    return {};
}

Path aStar(const RoadGraph& graph, RoadNode* start, RoadNode* end) {
    /* TODO: Delete the following lines and implement this function! */
    return aStarExclude(graph, start, end);
}

Path aStarExclude(const RoadGraph& graph, RoadNode* start, RoadNode* end, RoadEdge* exclude) {
    PriorityQueue<pair<Path, double>> pathQueue;

    Path path;
    path.add(start);
    double futureCost = graph.crowFlyDistanceBetween(start, end) / graph.maxRoadSpeed(); // this line is important
    pathQueue.enqueue(make_pair(path, 0), futureCost);  // future cost count toward priority but dont count toward path cost

    Set<RoadNode*> visited;

    while (!pathQueue.isEmpty() && !visited.contains(end)) {
        pair<Path, double> pathPair = pathQueue.dequeue();
        Path currentPath = pathPair.first;
        double currentCost = pathPair.second;

        RoadNode* nodeEnd = currentPath.get(currentPath.size() - 1);

        if (!visited.contains(nodeEnd)) {
            visited.add(nodeEnd);
            nodeEnd->setColor(Color::GREEN);

            if (nodeEnd == end) {
                return currentPath;
            }

            Set<RoadNode*> neighbors = graph.neighborsOf(nodeEnd);
            neighbors = neighbors.removeAll(visited);

            for (RoadNode* node: neighbors) {
                node->setColor(Color::YELLOW);

                if (exclude != nullptr && exclude->from() == nodeEnd && exclude->to() == node)
                    // exclude edge
                    continue;

                RoadEdge* edge = graph.edgeBetween(nodeEnd, node);

                double cost = currentCost + edge->cost();
                double futureCost = cost + graph.crowFlyDistanceBetween(node, end) / graph.maxRoadSpeed();

                Path newPath;
                newPath.addAll(currentPath);
                newPath.add(node);

                pathQueue.enqueue(make_pair(newPath, cost), futureCost);
            }
        }
    }

    // cant find path
    return {};
}

Path alternativeRoute(const RoadGraph& graph, RoadNode* start, RoadNode* end) {
    /* TODO: Delete the following lines and implement this function! */
    Path shortestPath = aStar(graph, start, end);
    PriorityQueue<Path> alternativeQueue;

    for (int i = 0; i < shortestPath.size() - 2; i++) {
        RoadEdge* exclude = graph.edgeBetween(shortestPath.get(i), shortestPath.get(i+1));
        double cost = 0;
        Path alternative = aStarExclude(graph, start, end, exclude);

        double different = 0.3;
        if (different > SUFFICIENT_DIFFERENCE) {
            alternativeQueue.enqueue(alternative, cost);
        }
    }
    return alternativeQueue.dequeue();
}


