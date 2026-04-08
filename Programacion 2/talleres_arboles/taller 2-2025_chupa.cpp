#include <iostream>
#include <vector>
#include "../include/ArbolN.hpp"

using namespace std;

struct NodeData {
	int nodeId;
	int efficiency;

	NodeData() : nodeId(0), efficiency(0) {}
	NodeData(int id, int value) : nodeId(id), efficiency(value) {}
};

struct Edge {
	int parentId;
	int childId;

	Edge() : parentId(0), childId(0) {}
	Edge(int parent, int child) : parentId(parent), childId(child) {}
};

struct CaseData {
	int nodeCount;
	vector<int> efficiencyById;
	vector<Edge> edges;

	CaseData() : nodeCount(0) {}
};

struct MsiState {
	long included;
	long excluded;

	MsiState() : included(0), excluded(0) {}
	MsiState(long inValue, long exValue) : included(inValue), excluded(exValue) {}
};

long maxLong(long a, long b) {
	return (a > b) ? a : b;
}

void appendChild(NodoN<NodeData>* parentPtr, NodoN<NodeData>* childPtr) {
	if (!parentPtr || !childPtr) {
		return;
	}

	NodoN<NodeData>* firstChild = parentPtr->getHijoIzq();
	if (!firstChild) {
		parentPtr->setHijoIzq(childPtr);
		return;
	}

	NodoN<NodeData>* lastChild = firstChild;
	while (lastChild->getHnoDer()) {
		lastChild = lastChild->getHnoDer();
	}
	lastChild->setHnoDer(childPtr);
}

NodoN<NodeData>* findNodeById(NodoN<NodeData>* currentPtr, int targetId) {
	if (!currentPtr) {
		return NULL;
	}

	if (currentPtr->getInfo().nodeId == targetId) {
		return currentPtr;
	}

	NodoN<NodeData>* childPtr = currentPtr->getHijoIzq();
	while (childPtr) {
		NodoN<NodeData>* foundPtr = findNodeById(childPtr, targetId);
		if (foundPtr) {
			return foundPtr;
		}
		childPtr = childPtr->getHnoDer();
	}

	return NULL;
}

void destroyTree(NodoN<NodeData>* rootPtr) {
	if (!rootPtr) {
		return;
	}

	NodoN<NodeData>* childPtr = rootPtr->getHijoIzq();
	while (childPtr) {
		NodoN<NodeData>* nextPtr = childPtr->getHnoDer();
		destroyTree(childPtr);
		childPtr = nextPtr;
	}

	delete rootPtr;
}

bool readCaseData(istream& input, CaseData& caseData) {
	if (!(input >> caseData.nodeCount)) {
		return false;
	}

	int nodeCount = caseData.nodeCount;
	caseData.efficiencyById.assign(nodeCount + 1, 0);
	caseData.edges.clear();

	for (int id = 1; id <= nodeCount; ++id) {
		input >> caseData.efficiencyById[id];
	}

	for (int i = 1; i <= nodeCount - 1; ++i) {
		int parentId;
		int childId;
		input >> parentId >> childId;
		caseData.edges.push_back(Edge(parentId, childId));
	}

	return true;
}

// Version A (preferida): construccion O(n) con acceso directo por id.
NodoN<NodeData>* buildTreeWithVector(const CaseData& caseData) {
	int nodeCount = caseData.nodeCount;
	if (nodeCount <= 0) {
		return NULL;
	}

	vector<NodoN<NodeData>*> nodeById(nodeCount + 1, NULL);

	for (int id = 1; id <= nodeCount; ++id) {
		NodeData nodeInfo(id, caseData.efficiencyById[id]);
		nodeById[id] = new NodoN<NodeData>(nodeInfo);
	}

	for (size_t i = 0; i < caseData.edges.size(); ++i) {
		int parentId = caseData.edges[i].parentId;
		int childId = caseData.edges[i].childId;

		if (parentId < 1 || parentId > nodeCount || childId < 1 || childId > nodeCount) {
			for (int id = 1; id <= nodeCount; ++id) {
				delete nodeById[id];
			}
			return NULL;
		}

		appendChild(nodeById[parentId], nodeById[childId]);
	}

	return nodeById[1];
}

// Version B (alternativa): construccion TAD puro sin vector, costo mayor.
NodoN<NodeData>* buildTreeWithoutVector(const CaseData& caseData) {
	int nodeCount = caseData.nodeCount;
	if (nodeCount <= 0) {
		return NULL;
	}

	NodoN<NodeData>* rootPtr = new NodoN<NodeData>(NodeData(1, caseData.efficiencyById[1]));
	vector<char> nodeInserted(nodeCount + 1, 0);
	vector<char> edgeInserted(caseData.edges.size(), 0);

	nodeInserted[1] = 1;
	int insertedEdges = 0;
	bool progress = true;

	while (insertedEdges < nodeCount - 1 && progress) {
		progress = false;

		for (size_t i = 0; i < caseData.edges.size(); ++i) {
			if (edgeInserted[i]) {
				continue;
			}

			int parentId = caseData.edges[i].parentId;
			int childId = caseData.edges[i].childId;

			if (parentId < 1 || parentId > nodeCount || childId < 1 || childId > nodeCount) {
				continue;
			}

			if (!nodeInserted[parentId] || nodeInserted[childId]) {
				continue;
			}

			NodoN<NodeData>* parentPtr = findNodeById(rootPtr, parentId);
			if (!parentPtr) {
				continue;
			}

			NodoN<NodeData>* childPtr = new NodoN<NodeData>(NodeData(childId, caseData.efficiencyById[childId]));
			appendChild(parentPtr, childPtr);

			nodeInserted[childId] = 1;
			edgeInserted[i] = 1;
			++insertedEdges;
			progress = true;
		}
	}

	if (insertedEdges != nodeCount - 1) {
		destroyTree(rootPtr);
		return NULL;
	}

	return rootPtr;
}

MsiState computeMsi(NodoN<NodeData>* currentPtr) {
	if (!currentPtr) {
		return MsiState(0, 0);
	}

	long included = currentPtr->getInfo().efficiency;
	long excluded = 0;

	NodoN<NodeData>* childPtr = currentPtr->getHijoIzq();
	while (childPtr) {
		MsiState childState = computeMsi(childPtr);
		included += childState.excluded;
		excluded += maxLong(childState.included, childState.excluded);
		childPtr = childPtr->getHnoDer();
	}

	return MsiState(included, excluded);
}

void countLeafParity(NodoN<NodeData>* currentPtr, int level, int& evenLeafCount, int& oddLeafCount) {
	if (!currentPtr) {
		return;
	}

	if (!currentPtr->getHijoIzq()) {
		if ((level % 2) == 0) {
			++evenLeafCount;
		} else {
			++oddLeafCount;
		}
		return;
	}

	NodoN<NodeData>* childPtr = currentPtr->getHijoIzq();
	while (childPtr) {
		countLeafParity(childPtr, level + 1, evenLeafCount, oddLeafCount);
		childPtr = childPtr->getHnoDer();
	}
}

long solveCase(const CaseData& caseData, bool useVectorVersion) {
	if (caseData.nodeCount <= 0) {
		return 0;
	}

	NodoN<NodeData>* rootPtr = useVectorVersion
		? buildTreeWithVector(caseData)
		: buildTreeWithoutVector(caseData);

	if (!rootPtr) {
		return 0;
	}

	MsiState rootState = computeMsi(rootPtr);
	long maxIndependentSum = maxLong(rootState.included, rootState.excluded);

	int evenLeafCount = 0;
	int oddLeafCount = 0;
	countLeafParity(rootPtr, 0, evenLeafCount, oddLeafCount);

	long balance = static_cast<long>(evenLeafCount - oddLeafCount);
	long chupaValue = maxIndependentSum * balance;

	destroyTree(rootPtr);
	return chupaValue;
}

int main() {
	int testCount;
	cin >> testCount;

	// Preferencia pedagógica: construir con vector para separar entrada y logica.
	const bool useVectorVersion = true;

	for (int caseIndex = 1; caseIndex <= testCount; ++caseIndex) {
		CaseData caseData;
		if (!readCaseData(cin, caseData)) {
			break;
		}

		long answer = solveCase(caseData, useVectorVersion);
		cout << answer;
		if (caseIndex < testCount) {
			cout << "\n";
		}
	}

	return 0;
}