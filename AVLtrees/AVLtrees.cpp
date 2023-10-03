#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Node {
public:
    int key;          // Kl�� uzlu, kter� reprezentuje hodnotu v uzlu.
    Node* left;       // Ukazatel na lev�ho potomka uzlu.
    Node* right;      // Ukazatel na prav�ho potomka uzlu.
    int height;       // V��ka uzlu v AVL stromu.

    // Konstruktor uzlu, kter� inicializuje kl�� na zadanou hodnotu a
    // nastavuje ukazatele na potomky na nullptr. V��ka uzlu je nastavena na 1.
    Node(int k) : key(k), left(nullptr), right(nullptr), height(1) {}
};


class AVLTree {
public:
    Node* root;

    // Konstruktor AVL stromu. Inicializuje ko�en stromu na nullptr.
    AVLTree() : root(nullptr) {}

    // Metoda pro z�sk�n� v��ky uzlu v r�mci AVL stromu.
    int height(Node* node) {
        if (node == nullptr) 
        {
            return 0;
        }

        return node->height; // Vr�t�me v��ku uzlu.
    }

    // Metoda pro v�po�et vyv�en� uzlu, co� je rozd�l v��ek lev�ho a prav�ho podstromu.
    int balanceFactor(Node* node) {
        if (node == nullptr) 
        {
            return 0;
        }

        // Vr�t�me rozd�l v��ek lev�ho a prav�ho podstromu
        return height(node->left) - height(node->right);
    }

    // Rotace po sm�ru hodinov�ch ru�i�ek (prav� rotace)
    Node* rotateRight(Node* y) {

        // Ulo�en� lev�ho potomka uzlu y do nov�ho uzlu x
        Node* x = y->left;

        // Ulo�en� prav�ho potomka (podstromu) uzlu x do T2
        Node* T2 = x->right;

        // Prov�d�me rotaci:
        // 1. P�esm�rov�n� prav�ho potomka uzlu x na y
        x->right = y;
        // 2. P�esm�rov�n� lev�ho potomka uzlu y na T2
        y->left = T2;

        // Aktualizace v��ek uzl� po rotaci.
        // V��ka uzlu y je maximem v��ek jeho lev�ho a prav�ho podstromu, zv���me o 1
        y->height = max(height(y->left), height(y->right)) + 1;
        // V��ka uzlu x je maximem v��ek jeho lev�ho a prav�ho podstromu, zv���me o 1
        x->height = max(height(x->left), height(x->right)) + 1;

        return x; // Vrac�me nov� ko�en (uzel x) po rotaci
    }


    // Rotace proti hodinov�m ru�i�k�m (lev� rotace).
    Node* rotateLeft(Node* x) {

        // Ulo��me prav�ho potomka uzlu x do y
        Node* y = x->right;

        // Ulo��me lev�ho potomka uzlu y do T2.
        Node* T2 = y->left;

        // Prov�d�me rotaci:
        // 1. P�esm�rov�n� lev�ho potomka uzlu y na x
        y->left = x;
        // 2. P�esm�rov�n� prav�ho potomka uzlu x na T2
        x->right = T2;

        // Aktualizace v��ek uzl� po rotaci.
        // V��ka uzlu x je maximem v��ek jeho lev�ho a prav�ho podstromu, zv���me o 1
        x->height = max(height(x->left), height(x->right)) + 1;
        // V��ka uzlu y je maximem v��ek jeho lev�ho a prav�ho podstromu, zv���me o 1
        y->height = max(height(y->left), height(y->right)) + 1;

        // Vrac�me nov� ko�en (uzel y) po rotaci 
        return y;
    }


    // Vlo�en� prvku do stromu
    Node* insert(Node* node, int key) {
        // Pokud je uzel pr�zdn�, vytvo��me nov� uzel s dan�m kl��em.
        if (node == nullptr)
        {
            return new Node(key);
        }

        // Porovn�me kl�� s kl��em aktu�ln�ho uzlu a rozhodneme, do kter�ho podstromu vlo�it.
        if (key < node->key)
        {
            node->left = insert(node->left, key);
        }
        else if (key > node->key)
        {
            node->right = insert(node->right, key);
        }
        else
        {
            return node; // Duplicitn� kl��, uzel ji� existuje, neprov�d�me vkl�d�n�.
        }

        // Aktualizace v��ky tohoto uzlu po vlo�en� potomka.
        node->height = 1 + max(height(node->left), height(node->right));

        // Zkontrolujeme vyv�en� a provedeme rotace, pokud je t�eba.

        int balance = balanceFactor(node);

        // LL rotace
        // Kdy� se vyv�en� uzlu stane v�t��m ne� 1 a probl�m je v lev�m podstromu uzlu a je�t� v�ce v lev�m podstromu tohoto lev�ho uzlu.
        if (balance > 1 && key < node->left->key) 
        {
            return rotateRight(node);
        }


        // RR rotace
        // Kdy� se vyv�en� uzlu stane men��m ne� -1 a probl�m je v prav�m podstromu uzlu a je�t� v�ce v prav�m podstromu tohoto prav�ho uzlu.
        if (balance < -1 && key > node->right->key) {
            return rotateLeft(node);
        }


        // LR rotace
        // Kdy� se vyv�en� uzlu stane v�t��m ne� 1 a probl�m je v lev�m podstromu uzlu, ale v�ce v prav�m podstromu tohoto lev�ho uzlu.
        if (balance > 1 && key > node->left->key) 
        {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        // RL rotace
        // Kdy� se vyv�en� uzlu stane men��m ne� -1 a probl�m je v prav�m podstromu uzlu, ale v�ce v lev�m podstromu tohoto prav�ho uzlu.
        if (balance < -1 && key < node->right->key) 
        {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    // In-order pr�chod stromem (v�pis)
    void inOrderTraversal(Node* node) {
        if (node != nullptr) {
            inOrderTraversal(node->left);
            cout << node->key << " ";
            inOrderTraversal(node->right);
        }
    }

    void printTreeLevelOrder() {
        // Pokud je ko�en stromu nullptr, strom je pr�zdn�, a nen� co vypisovat.
        if (root == nullptr)
        {
            return;
        }

        // Vytvo�en� fronty pro uchov�n� uzl� stromu.
        queue<Node*> q;

        // Vlo�en� ko�ene stromu do fronty.
        q.push(root);

        // Vlo�en� nullptr jako odd�lova�e �rovn�.
        q.push(nullptr); // Odd�lova� �rovn�

        // Hlavn� smy�ka pro pr�chod stromem �rove� po �rovni.
        while (!q.empty()) {
            // Z�sk�n� aktu�ln�ho uzlu z fronty.
            Node* current = q.front();
            q.pop();

            // Pokud aktu�ln� uzel je nullptr, dos�hli jsme konce �rovn�.
            if (current == nullptr) {
                // Vytiskneme nov� ��dek, aby byly uzly jednotliv�ch �rovn� odd�leny.
                cout << endl;

                // Pokud fronta nen� pr�zdn� (dal�� �rove� uzl�), p�id�me dal�� nullptr jako odd�lova� �rovn�.
                if (!q.empty())
                {
                    q.push(nullptr);
                }
            }
            else {
                // Vyp�eme hodnotu aktu�ln�ho uzlu, odd�lenou mezerou.
                cout << current->key << " ";

                // Pokud m� aktu�ln� uzel lev�ho potomka, p�id�me ho do fronty.
                if (current->left != nullptr) {
                    q.push(current->left);
                }

                // Pokud m� aktu�ln� uzel prav�ho potomka, p�id�me ho do fronty.
                if (current->right != nullptr)
                {
                    q.push(current->right);
                }
            }
        }
    }
};

int main()
{
    vector<int> avlVector = { 20, 10, 5, 13, 18, 25, 26, 27, 28, 12 };
    AVLTree avlTree;

    for (int key : avlVector) {
        avlTree.root = avlTree.insert(avlTree.root, key);
    }

    cout << "Serazeny vypis: " << endl;
    avlTree.inOrderTraversal(avlTree.root);
    cout << endl << endl;

    cout << "Serazeny vypis odshora dolu po radcich: " << endl;
    avlTree.printTreeLevelOrder();
    cout << endl;


    return 0;
}