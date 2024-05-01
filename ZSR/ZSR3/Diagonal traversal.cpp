// Autor: Muhamed Husić
vector<int> diagonalTraversal(vector<vector<int>>& mat) {
        long unsigned int elements{mat.size() * mat[0].size()};
        std::vector<int> arr(elements);
        int brojac{}, k{}, j_counter{}, i_counter{};
        int max = mat.size();
        if(max < mat[0].size()) {
            max = mat[0].size();
        }
        int last_index = arr.size() - 1;
        while(brojac < max) {
            int i, j;
            if(brojac % 2 == 0) {
                if(brojac >= mat.size()) {
                    i = mat.size() - 1;
                    j = i + j_counter;
                    j_counter += 2;
                } else {
                    i = brojac;
                    j = 0;
                }
                for(; i >= 0 && j < mat[0].size(); i--) {
                    arr[last_index--] = mat[mat.size() - 1 - i][mat[0].size() - 1 - j];
                    arr[k++] = mat[i][j++];
                    elements -= 2;
                }
            } else {
                if(brojac >= mat[0].size()) {
                    j = mat[0].size() - 1;
                    i = j + i_counter;
                    i_counter += 2;
                } else {
                    j = brojac;
                    i = 0;
                }
                for(; j >= 0 && i < mat.size(); j--) {
                    arr[last_index--] = mat[mat.size() - 1 - i][mat[0].size() - 1 - j];
                    arr[k++] = mat[i++][j];
                    elements -= 2;
                }
            }
            if(elements <= 0) {
                break;
            }
            brojac++;
        }
        if(max % 2 && mat.size() != mat[0].size()) {
            for(int i=max; i < mat.size() * mat[0].size() - 1; i+=2) {
                std::swap(arr[i], arr[i+1]);
            }
        }
        return arr;
    }
};