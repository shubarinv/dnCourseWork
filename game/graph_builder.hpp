//
// Created by vhundef on 07.01.2020.
//

#ifndef DNCOURSEWORK_GRAPH_BUILDER_HPP
#define DNCOURSEWORK_GRAPH_BUILDER_HPP


#include "graph.hpp"
#include "../Lib/tinyexpr.h"
#include <algorithm>
#include <iostream>

using namespace std;

class GraphBuilder {
private:
    Graph *graph;

    void findAndReplaceAll(std::string &data, std::string toSearch, std::string replaceStr) {
        // Get the first occurrence
        size_t pos = data.find(toSearch);

        // Repeat till end is reached
        while (pos != std::string::npos) {
            // Replace this occurrence of Sub String
            data.replace(pos, toSearch.size(), replaceStr);
            // Get the next occurrence from the current position
            pos = data.find(toSearch, pos + replaceStr.size());
        }
    }

public:
    GraphBuilder(Graph *_graph) {
        if (_graph == nullptr) {
            throw std::runtime_error("GraphBuilder::GraphBuilder _graph is null!");
        }
        graph = _graph;
    }

    void buildGraph(std::string expression) {
        for (int i = -graph->getWindowWidth() / 10; i <= graph->getWindowWidth() / 10; i++) {
            cout << "---------------------" << endl;
            string y1 = expression;
            cout << "y1:" << y1 << endl;
            findAndReplaceAll(y1, "x", to_string(i));
            cout << "y1:" << y1 << endl;

            string y2 = expression;
            cout << "y2:" << y2 << endl;
            findAndReplaceAll(y2, "x", to_string(i + 1));
            cout << "y2:" << y2 << endl;

            graph->addLine({i, (int) te_interp(y1.c_str(), 0), i + 1, (int) te_interp(y2.c_str(), 0)},
                           {255, 0, 0, 255});
        }
    }

};


#endif //DNCOURSEWORK_GRAPH_BUILDER_HPP
