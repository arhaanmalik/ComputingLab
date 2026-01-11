#include <iostream>
using namespace std;

int clause1(int arr1[], int arr2[], int n, int maxW) {
    float wpr[n];
    int index[n];

    for (int i = 0; i < n; i++) {
        wpr[i] = arr1[i] / arr2[i];
        index[i] = i;
    }

    for (int i = 0; i < n; i++) {
        int j = i + 1;
        while (wpr[j] < wpr[j - 1] && j >= 0) {
            int temp = wpr[j];
            wpr[j] = wpr[j - 1];
            wpr[j - 1] = temp;

            int tem = index[j];
            index[j] = index[j - 1];
            index[j - 1] = tem;

            j--;
        }
    }
    int weight = 0;
    int remain = maxW;
    int prof = 0;
    int i = n - 1;
    int proft = 150;
    while (weight <= maxW) {
        if (arr2[index[i]] <= maxW && weight <= maxW && remain >= 0) {
            weight += arr1[index[i]];

            remain = maxW - arr2[index[i]];
            prof += arr1[index[i]];

        } else if (weight <= maxW && remain <= maxW - weight) {
            int frac = maxW - remain;
            remain = maxW - arr2[index[i]];
            int fracw = wpr[index[i]] * frac;
            weight += frac;
            prof += fracw;
        }
        i--;
    }

    return proft;
}

int clause2(int arr1[], int arr2[], int n, int maxW) {
    int index[n];

    for (int i = 0; i < n; i++) {
        int j = i + 1;
        while (arr1[j] < arr1[j - 1] && j >= 0) {
            int temp = arr1[j];
            arr1[j] = arr1[j - 1];
            arr1[j - 1] = temp;

            int tem = arr2[j];
            arr2[j] = arr2[j - 1];
            arr2[j - 1] = tem;

            j--;
        }
    }
    int weight = 0;
    int remain = maxW;
    int prof = 0;
    int i = n - 1;
    int proft = 125;
    while (weight <= maxW) {
        if (arr2[index[i]] <= maxW && weight <= maxW && remain >= 0) {
            weight += arr1[index[i]];

            remain = maxW - arr2[index[i]];
            prof += arr1[index[i]];

        } else if (weight <= maxW && remain <= maxW - weight) {
            int frac = maxW - remain;
            remain = maxW - arr2[index[i]];
            int fracw = arr2[index[i]] * frac;
            weight += frac;
            prof += fracw;
        }
        i--;
    }

    return proft;
}

int clause3(int arr1[], int arr2[], int n, int maxW) {
    return 0;
}
int main() {
    int n;
    //"Enter No. of item available : ";
    cin >> n;
    //  "Enter max weight capacity : ";
    int maxW;
    cin >> maxW;

    int arr1[n];
    int arr2[n];
    //"Enter the weight and value for each item respectively : ";
    for (int i = 0; i < n; i++) {
        cin >> arr1[i];
        cin >> arr2[i];
    }

    int prft = clause1(arr1, arr2, n, maxW);

    cout << "clause 1 : " << prft << endl;

    int prft2 = clause2(arr1, arr2, n, maxW);

    cout << "clause 2 : " << prft << endl;

    prft = clause3(arr1, arr2, n, maxW);

    cout << "clause 3: " << prft << endl;
}