/*
 * IOI14P3.cpp
 *
 *  Created on: May 27, 2017
 *      Author: Wesley Leung
 */

#include <bits/stdc++.h>

#define MAXN 1500

using namespace std;

int cc[MAXN][MAXN];
int N;

struct WeightedUF {
private:
	int* parent;
	int* size;
	int count;

public:
    /**
     * Initializes an empty union–find data structure with {@code n} sites
     * {@code 0} through {@code n-1}. Each site is initially in its own
     * component.
     *
     * @param  n the number of sites
     */
    WeightedUF(int n) {
        count = n;
        parent = new int[n];
        size = new int[n];
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            size[i] = 1;
        }
    }

    /**
     * Returns the number of components.
     *
     * @return the number of components (between {@code 1} and {@code n})
     */
    int getCount() {
        return count;
    }


    /**
     * Returns the component identifier for the component containing site {@code p}.
     *
     * @param  p the integer representing one site
     * @return the component identifier for the component containing site {@code p}
     */
    int find(int p) {
        int root = p;
        while (root != parent[root])
            root = parent[root];
        while (p != root) {
            int newp = parent[p];
            parent[p] = root;
            p = newp;
        }
        return root;
    }

   /**
     * Returns true if the the two sites are in the same component.
     *
     * @param  p the integer representing one site
     * @param  q the integer representing the other site
     * @return {@code true} if the two sites {@code p} and {@code q} are in the same component;
     *         {@code false} otherwise
     */
    bool connected(int p, int q) {
        return find(p) == find(q);
    }

    /**
     * Returns the size of the component containing p
     *
     * @param p the integer representing one site
     * @return the size of the component containing p
     */
    int getSize(int p) {
    	return size[find(p)];
    }

    /**
     * Merges the component containing site {@code p} with the
     * the component containing site {@code q}.
     *
     * @param  p the integer representing one site
     * @param  q the integer representing the other site
     */
    void join(int p, int q) {
        int rootP = find(p);
        int rootQ = find(q);
        if (rootP == rootQ) return;

        // make smaller root point to larger one
        if (size[rootP] < size[rootQ]) {
            parent[rootP] = rootQ;
            size[rootQ] += size[rootP];
            for (int i = 0; i < N; i++) {
            	if (i == rootQ) continue;
				cc[rootQ][i] += cc[rootP][i];
			}
        }
        else {
            parent[rootQ] = rootP;
            size[rootP] += size[rootQ];
            for (int i = 0; i < N; i++) {
            	if (i == rootP) continue;
            	cc[rootP][i] += cc[rootQ][i];
            }
        }
        count--;
    }

    /**
     * Unmerges the component containing site {@code p} with the
     * the component containing site {@code q}.
     *
     * @param  p the integer representing one site
     * @param  q the integer representing the other site
     */
    void disjoin(int p, int q) {
        int rootP = find(p);
        int rootQ = find(q);
        if (rootP == rootQ) return;

        // make smaller root point to larger one
        if (size[rootP] < size[rootQ]) {
            parent[rootP] = rootP;
            size[rootQ] -= size[rootP];
        }
        else {
            parent[rootQ] = rootQ;
            size[rootP] -= size[rootQ];
        }
        count++;
    }
};

WeightedUF* uf;

void initialize(int n) {
	N = n;
	uf = new WeightedUF(n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i != j) cc[i][j] = 1;
		}
	}
}

int hasEdge(int u, int v) {
	int rootU = uf->find(u);
	int rootV = uf->find(v);
	if (rootU == rootV) {
		cc[rootU][rootV]--;
		cc[rootV][rootU]--;
		return 1;
	}
	int countU = 0;
	int countV = 0;
	for (int i = 0; i < N; i++) {
		countU += cc[rootU][i];
		countV += cc[rootV][i];
	}
	cc[rootU][rootV]--;
	cc[rootV][rootU]--;
	if (countU == 1 || countV == 1 || (uf->getSize(rootU) == 1 && uf->getSize(rootV) == 1)) {
		uf->join(u, v);
		return 1;
	}
	return 0;
}

int main() {
	int n;
	scanf("%d", &n);
	initialize(n);
	int r = n * (n - 1) / 2;
	for (int i = 0; i < r; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		printf("%d\n", hasEdge(u, v));
	}
	return 0;
}
