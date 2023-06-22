#include <iostream>
#include <string>
using namespace std;

struct Pokemon
{
    int power;
    string name;
    string type;
};

struct Node
{
    Pokemon pokemon;
    Node *left;
    Node *right;
};

Node *newNode(int power, const string &name, const string &type)
{
    Node *node = new Node();
    node->pokemon.power = power;
    node->pokemon.name = name;
    node->pokemon.type = type;
    node->left = NULL;
    node->right = NULL;
    return node;
}

Node *insert(Node *root, int power, const string &name, const string &type)
{
    if (root == NULL)
    {
        root = newNode(power, name, type);
        return root;
    }

    if (power < root->pokemon.power)
    {
        root->left = insert(root->left, power, name, type);
    }
    else if (power >= root->pokemon.power)
    {
        root->right = insert(root->right, power, name, type);
    }

    return root;
}

void inOrder(Node *root)
{
    if (root == NULL)
    {
        return;
    }
    inOrder(root->left);
    cout << "Poder: " << root->pokemon.power << endl;
    cout << "Nome: " << root->pokemon.name << endl;
    cout << "Tipo: " << root->pokemon.type << endl;
    cout << "-----------------------" << endl;
    inOrder(root->right);
}

void printMenu()
{
    cout << endl;
    cout << "##########  Bem-vindo à Pokédex!  ##########" << endl;
    cout << endl;
    cout << "Digite 1 para adicionar um pokémon na Pokédex," << endl;
    cout << "2 para remover um pokémon," << endl;
    cout << "3 para procurar um pokémon," << endl;
    cout << "4 para ver quais são os pokémons cadastrados" << endl;
    cout << "5 para sair da Pokédex" << endl;
    cout << endl;
}

void printSeparator()
{
    cout << endl;
    cout << "-----------------------" << endl;
    cout << endl;
}

void adicionarPokemon(Node *&root)
{
    int continuar = 1;

    do
    {
        int power = -1;
        string name = "";
        string type = "";

        printSeparator();

        cout << "Digite o nome do Pokémon: ";
        cin.ignore();
        getline(cin, name);

        do
        {
            cout << "Digite o poder do Pokémon (0 a 10): ";
            cin >> power;
        } while (power < 0 || power > 10);

        cout << "Digite o tipo do Pokémon: ";
        cin.ignore();
        getline(cin, type);

        root = insert(root, power, name, type);
        printSeparator();

        cout << "Pokémon adicionado, digite 0 para sair do cadastro de pokémon ou 1 para cadastrar outro:" << endl;
        cin >> continuar;
    } while (continuar != 0);
}

Node *deleteNode(Node *root, int power)
{
    if (root == NULL)
        return root;

    if (power < root->pokemon.power)
    {
        root->left = deleteNode(root->left, power);
    }
    else if (power > root->pokemon.power)
    {
        root->right = deleteNode(root->right, power);
    }
    else
    {
        if (root->left == NULL)
        {
            Node *temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == NULL)
        {
            Node *temp = root->left;
            delete root;
            return temp;
        }

        Node *minRight = root->right;
        while (minRight->left != NULL)
            minRight = minRight->left;

        root->pokemon = minRight->pokemon;
        root->right = deleteNode(root->right, minRight->pokemon.power);
    }
    return root;
}

Node *searchPokemonByPower(Node *root, int power)
{
    if (root == NULL || root->pokemon.power == power)
        return root;

    if (power < root->pokemon.power)
        return searchPokemonByPower(root->left, power);

    return searchPokemonByPower(root->right, power);
}

void buscarPokemon(Node *root)
{
    int power;
    printSeparator();
    cout << "Digite o poder do Pokémon que deseja buscar: ";
    cin >> power;

    Node *pokemon = searchPokemonByPower(root, power);

    if (pokemon != NULL)
    {
        cout << endl;
        cout << "Pokémon encontrado:" << endl;
        cout << "Poder: " << pokemon->pokemon.power << endl;
        cout << "Nome: " << pokemon->pokemon.name << endl;
        cout << "Tipo: " << pokemon->pokemon.type << endl;
    }
    else
    {
        cout << "Pokémon não encontrado na Pokédex." << endl;
    }

    printSeparator();
}

int main()
{
    Node *root = NULL;

    int choice = 0;
    while (choice != 5)
    {
        printMenu();
        cout << ">";
        cin >> choice;

        if (choice == 1)
        {
            // Add a Pokémon
            adicionarPokemon(root);
        }
        else if (choice == 2)
        {
            // Remove a Pokémon
            int power;
            printSeparator();
            cout << "Digite o poder do Pokémon que deseja remover: ";
            cin >> power;

            root = deleteNode(root, power);
            printSeparator();
            cout << "Pokémon removido da Pokédex." << endl;
            printSeparator();
        }
        else if (choice == 3)
        {
            // Search for a Pokémon by power
            buscarPokemon(root);
        }
        else if (choice == 4)
        {
            // Print the Pokédex
            cout << "Pokédex em ordem:" << endl;
            cout << endl;
            inOrder(root);
        }
        else if (choice == 5)
        {
            cout << "Saindo da Pokédex..." << endl;
        }
        else
        {
            printSeparator();
            cout << "Opção inválida! Digite novamente." << endl;
            printSeparator();
        }
    }

    return 0;
}
