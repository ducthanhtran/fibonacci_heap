#ifndef FIBONACCI_HEAP_HPP
#define FIBONACCI_HEAP_HPP

#include <memory>
#include <optional>
#include <utility>

#include <iostream>

template<typename Key>
class FibonacciHeap
{
    struct Node
    {
        Node(Key k) : key(k) {}

        bool isMarked = false;
        unsigned int degree = 0;
        Node* left = nullptr;
        Node* right = nullptr;
        Node* parent = nullptr;
        Node* child = nullptr;
        Key key;
        friend std::ostream& operator<<(std::ostream& os, Node& v) {
            return os << &v << ": {Marked:" << v.isMarked << " deg:" << v.degree << " L:" << v.left
                    << " R:" << v.right << " Parent:" << v.parent << " Child:" << v.child << '}';
        }
    };

    public:
        FibonacciHeap() : m_numNodes(0), m_min(nullptr) {}

        const Node* min_node() const
        {
            return m_min;
        }

        unsigned int num_nodes() const
        {
            return m_numNodes;
        }

        std::optional<Key> min() const
        {
            if (m_min)
            {
                return m_min->key;
            }
            return std::nullopt;
        }

        void merge(FibonacciHeap &other)
        {
            // TODO: write test
            if (m_min == nullptr && other.m_min != nullptr)
            {
                this->m_min = other.m_min;
                this->m_numNodes = other.m_numNodes;
            }
            else if (m_min != nullptr && other.m_min != nullptr)
            {
                auto otherRight = other.m_min->right;
                auto right = this->m_min->right;

                other.m_min->right = this->m_min;
                m_min->right = other.m_min;

                otherRight->left = right;
                right->left = otherRight;

                if (other.m_min->key < m_min->key)
                {
                    this->m_min = other.m_min;
                }
                this->m_numNodes += other.m_numNodes;

                // TODO: Invalidate other
            }
        }

        Node* insert(const Key k)
        {
            ++m_numNodes;
            auto newNode = new Node(k);
            if (!m_min) 
            {
                m_min = newNode;
                m_min->left = m_min;
                m_min->right = m_min;
                return m_min; // TODO: maybe shared_ptr?
            }
            else
            {
                // Add newNode to the left of m_min
                auto leftNode = m_min->left;

                newNode->left = leftNode;
                newNode->right = m_min;
                leftNode->right = newNode;
                m_min->left = newNode;

                if (k < m_min->key)
                {
                    m_min = newNode;
                }
                return newNode; // TODO: maybe shared_ptr?
            }
        }

        std::optional<Node> extract_min()
        {
            if (m_min == nullptr)
            {
                return std::nullopt;
            }
            else
            {
                const auto minKey = m_min->key;

                if (m_min->children != nullptr)
                {
                    // Merge children of m_min into root level
                    auto left = m_min->left;
                    auto child = m_min->child;
                    for(auto i = 0; i < m_min->degree - 1; ++i)
                    {
                        left->right = child;
                        child->parent = nullptr;
                        left = child;
                        child = child->right;
                    }
                    // Last child enforces circular root list with right-neighbor of m_min
                    auto right = m_min->right;
                    right->left = child;
                    child->right = right;
                    child->parent = nullptr;
                }

                if (m_min.right == m_min)
                {
                    delete m_min;
                    m_min = nullptr;
                    return minKey;
                }
                else
                {
                    // TODO: consolidate
                    // // Find new mininum node and delete current m_min
                    // auto newMin = m_min->right;
                    // for(auto next = m_min->right->right; next != m_min->right; next = next->right)
                    // {
                    //     if (next->key < newMin->key)
                    //     {
                    //         newMin = next;
                    //     }
                    // }
                    delete m_min;
                }
            }
        }

    private:
        unsigned int m_numNodes;
        Node* m_min;
};

#endif