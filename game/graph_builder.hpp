

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

    void buildGraph(uiFunctionsRecord *record) {
        double i = -graph->getWindowWidth() / 20;
        const string &expression = record->getFunction();
        while (i <= graph->getWindowWidth() / 20) {
	        cout << "---------------------" << endl;
	        string y1 = expression;
	        cout << "y1:" << y1 << endl;
	        findAndReplaceAll(y1, "x", to_string(i));
	        cout << "y1:" << y1 << endl;

	        string y2 = expression;
	        cout << "y2:" << y2 << endl;
	        findAndReplaceAll(y2, "x", to_string(i + 0.1));
	        cout << "y2:" << y2 << endl;
	        int *error = nullptr;
	        double y1_val = te_interp(y1.c_str(), error) * 10;
	        if (error != nullptr || (int) y1_val == -2147483648) {
		        record->getDeleteBtn()->setEnabled(false);
		        cout << "ERROR IN EXPR" << endl;
		        break;
	        }
	        double y2_val = te_interp(y2.c_str(), error) * 10;
	        if (error != nullptr || (int) y2_val == -2147483648) {
		        record->getDeleteBtn()->setEnabled(false);
		        cout << "ERROR IN EXPR" << endl;
		        break;
	        }
	        graph->addLine({(int) (i * 10), (int) (y1_val), (int) ((i + 0.1) * 10),
	                        (int) (y2_val)},
	                       record->getColor(), record);
	        i += 0.1;
        }
    }

};


#endif //DNCOURSEWORK_GRAPH_BUILDER_HPP
