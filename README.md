# TP4 : BST et AVL - Rapport

## Table des matières
1. [Introduction](#introduction)
2. [Structures de données](#structures-de-données)
3. [Arbres Binaires de Recherche (BST)](#arbres-binaires-de-recherche-bst)
4. [Arbres AVL](#arbres-avl)
5. [File FIFO](#file-fifo)
6. [Compilation et exécution](#compilation-et-exécution)
7. [Résultats des tests](#résultats-des-tests)
8. [Analyse comparative](#analyse-comparative)
9. [Conclusion](#conclusion)

## Introduction

Ce projet implémente deux types d'arbres binaires en C :
- **BST (Binary Search Tree)** : Arbres binaires de recherche classiques
- **AVL** : Arbres binaires de recherche auto-équilibrés

L'objectif est de comprendre les différences de performance entre un arbre binaire de recherche simple et un arbre AVL qui maintient son équilibre automatiquement.

## Structures de données

### Structure BSTNode

```c
typedef struct _BSTNode{
    Elmt_t * data;           // Pointeur vers la donnée (int)
    struct _BSTNode * ls;    // Left son (fils gauche)
    struct _BSTNode * rs;    // Right son (fils droit)
}BSTNode;

typedef BSTNode* BST;
```

**Propriété d'ordre** : Pour chaque nœud n :
- Tous les éléments du sous-arbre gauche sont plus petits que n
- Tous les éléments du sous-arbre droit sont plus grands que n

### Structure AVLNode

```c
typedef struct _AVLNode{
    Elmt_t * data;           // Pointeur vers la donnée (int)
    struct _AVLNode * ls;    // Left son (fils gauche)
    struct _AVLNode * rs;    // Right son (fils droit)
    int bf;                  // Balance factor (facteur d'équilibrage)
}AVLNode;

typedef AVLNode* AVL;
```

**Facteur d'équilibrage** : `bf = hauteur(sous-arbre droit) - hauteur(sous-arbre gauche)`
- Dans un AVL, bf ∈ {-1, 0, 1} (sauf transitoirement lors d'ajout/suppression)

## Arbres Binaires de Recherche (BST)

### Fonctions de base

#### Création et tests
```c
BST create_empty_BST()           // Renvoie NULL
int is_empty_bst(BST)            // Renvoie 1 si arbre vide, 0 sinon
int is_leaf(BSTNode*)            // Renvoie 1 si feuille, 0 sinon
BSTNode* create_node(Elmt_t*)    // Alloue et initialise un nouveau nœud
```

#### Ajout d'éléments
```c
void add(Elmt_t*, BST*, int (*compare_elmt)(Elmt_t*, Elmt_t*))
```

**Algorithme récursif** :
1. Si l'arbre est vide, créer un nouveau nœud à la racine
2. Si x < racine, ajouter récursivement dans le sous-arbre gauche
3. Si x > racine, ajouter récursivement dans le sous-arbre droit
4. Si x = racine, ne rien faire (pas de doublons)

### Parcours de l'arbre

Quatre types de parcours sont implémentés :

#### 1. Parcours préfixé (prefix)
**Ordre** : Racine → Gauche → Droit
```c
void visit_prefix(BST t, void (*action)(BST*))
```

#### 2. Parcours infixé (infix)
**Ordre** : Gauche → Racine → Droit
```c
void visit_infix(BST t, void (*action)(BST*))
```
⚠️ Ce parcours affiche les éléments dans l'ordre croissant pour un BST !

#### 3. Parcours postfixé (postfix)
**Ordre** : Gauche → Droit → Racine
```c
void visit_postfix(BST t, void (*action)(BST*))
```
💡 Utilisé pour libérer la mémoire (enfants d'abord, racine en dernier)

#### 4. Parcours en largeur (breadth-first)
**Ordre** : Niveau par niveau, de gauche à droite
```c
void visit_bf(BST t, void (*action)(BST*))
```
Utilise une FIFO pour parcourir l'arbre niveau par niveau.

### Rotations

Les rotations sont des opérations fondamentales pour rééquilibrer les arbres.

#### Rotation gauche
```c
void rotate_left(BST* a)
```
```
    A                B
     \              / \
      B     =>     A   C
       \
        C
```

#### Rotation droite
```c
void rotate_right(BST* a)
```
```
      A            B
     /            / \
    B      =>    C   A
   /
  C
```

### Libération de mémoire
```c
void free_node(BST* t)      // Libère un nœud
void free_BST(BST* t)       // Libère tout l'arbre (parcours postfixé)
```

## Arbres AVL

Un arbre AVL est un BST qui maintient automatiquement son équilibre lors des insertions.

### Propriété AVL
Pour chaque nœud, |bf| ≤ 1 où bf = hauteur(droit) - hauteur(gauche)

### Fonctions spécifiques AVL

#### Rotations avec mise à jour des facteurs d'équilibrage

**Rotation gauche** :
```c
void rotate_left_avl(AVL* a)
```
- `bf(A) = bf(A) - max(bf(B), 0) - 1`
- `bf(B) = min(bf(A) - 2, bf(A) + bf(B) - 2, bf(B) - 1)`

**Rotation droite** :
```c
void rotate_right_avl(AVL* a)
```
- `bf(A) = bf(A) - min(bf(B), 0) + 1`
- `bf(B) = max(bf(A) + 2, bf(A) + bf(B) + 2, bf(B) + 1)`

#### Équilibrage
```c
void balance(AVL* a)
```

**Algorithme** :
1. Si bf = 2 (déséquilibre à droite) :
   - Si bf(fils droit) < 0 : rotation droite du fils droit
   - Rotation gauche de la racine
2. Si bf = -2 (déséquilibre à gauche) :
   - Si bf(fils gauche) > 0 : rotation gauche du fils gauche
   - Rotation droite de la racine

#### Ajout avec équilibrage
```c
int add_avl(Elmt_t*, AVL*, int (*compare_elmt)(Elmt_t*, Elmt_t*))
```

**Différences avec BST** :
- Renvoie la variation de hauteur (0 ou 1)
- Met à jour le facteur d'équilibrage après chaque ajout
- Appelle `balance()` si nécessaire
- Remonte la variation de hauteur au parent

## File FIFO

Implémentation d'une file FIFO (First In First Out) utilisée pour le parcours en largeur.

### Structure
```c
typedef struct _cell{
    void * data;
    struct _cell * next;
}Cell;

typedef struct{
    Cell* first;
    Cell* last;
}Fifo;
```

### Opérations
```c
Fifo create_fifo()              // Crée une FIFO vide
int is_empty(Fifo)              // Teste si la FIFO est vide
Cell* fifo_add(Fifo*, void*)    // Ajoute un élément à la fin
void* fifo_get(Fifo*)           // Retire et renvoie le premier élément
```

## Compilation et exécution

### Compilation du test BST
```bash
gcc -o test_bst test.c bst.c fifo.c Elmt.c -Wall
./test_bst
```

### Compilation du test AVL
```bash
gcc -o test_avl_prog test_avl.c avl.c fifo.c Elmt.c -Wall
./test_avl_prog
```

## Résultats des tests

### Test BST (insertion séquentielle 1, 2, 3, 4, 5)

```
Affichage prefixé : 
 1  2  3  4  5 
Affichage infixé : 
 1  2  3  4  5 
Affichage postfixé : 
 5  4  3  2  1 
Affichage largeur : 
 1  2  3  4  5
```

**Structure de l'arbre** :
```
1
 \
  2
   \
    3
     \
      4
       \
        5
```

⚠️ **Problème** : L'arbre est complètement déséquilibré ! Il ressemble à une liste chaînée.
- **Complexité de recherche** : O(n) au lieu de O(log n)

### Test AVL (insertion 5, 3, 7, 2, 4, 6, 8, 1, 9, 10)

```
Affichage prefixé : 
 5  3  2  1  4  7  6  9  8  10 
Affichage infixé : 
 1  2  3  4  5  6  7  8  9  10 
Affichage postfixé : 
 1  2  4  3  6  8  10  9  7  5 
Affichage largeur : 
 5  3  7  2  4  6  9  1  8  10
```

**Structure de l'arbre** :
```
       5
      / \
     3   7
    / \ / \
   2  4 6  9
  /      / \
 1      8  10
```

✅ **Succès** : L'arbre est équilibré !
- Tous les nœuds ont un facteur d'équilibrage ∈ {-1, 0, 1}
- **Complexité de recherche** : O(log n) garanti

## Analyse comparative

### BST vs AVL

| Aspect | BST | AVL |
|--------|-----|-----|
| **Insertion** | O(h) où h peut être n | O(log n) garanti |
| **Recherche** | O(h) où h peut être n | O(log n) garanti |
| **Mémoire** | 2 pointeurs par nœud | 2 pointeurs + 1 int par nœud |
| **Complexité insertion** | Simple | Rotations + MAJ bf |
| **Cas défavorable** | Liste chaînée | Toujours équilibré |

### Quand utiliser quoi ?

**BST** :
- ✅ Insertions aléatoires (l'arbre reste relativement équilibré)
- ✅ Implémentation simple
- ❌ Insertions séquentielles (dégénère en liste)

**AVL** :
- ✅ Garantie de performance O(log n)
- ✅ Nombreuses recherches
- ✅ Données séquentielles
- ❌ Légèrement plus complexe
- ❌ Surcoût mémoire (facteur d'équilibrage)

## Conclusion

Ce TP a permis de :

1. ✅ **Implémenter un BST complet** avec les 4 types de parcours
2. ✅ **Comprendre les limites du BST** : insertion séquentielle → dégénérescence
3. ✅ **Implémenter un AVL** avec rotations et équilibrage automatique
4. ✅ **Comparer BST et AVL** : performance vs complexité
5. ✅ **Utiliser une FIFO** pour le parcours en largeur

### Points clés

- Le **parcours infixé** d'un BST donne les éléments triés
- Le **parcours postfixé** est idéal pour libérer la mémoire
- Les **rotations** sont la clé de l'équilibrage
- Un **AVL** garantit O(log n) au prix d'une complexité accrue
- Le **facteur d'équilibrage** permet de détecter et corriger les déséquilibres

### Améliorations possibles

- [ ] Implémentation de la suppression dans un AVL
- [ ] Affichage graphique avec ascii_art (fichiers .o non fournis)
- [ ] Mesure de performance (temps d'exécution, nombre de rotations)
- [ ] Implémentation d'autres arbres équilibrés (Red-Black, B-trees)
- [ ] Tests unitaires complets
- [ ] Gestion des doublons (multimap)

---

**Auteur** : kiks772  
**Date** : 2025  
**Cours** : Structures de données - Arbres binaires
