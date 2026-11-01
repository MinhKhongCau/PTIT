# Decision Tree & Random Forest & Bootsing

# Decision tree

**Core concept** A decision tree is a tree-like structure that is used to make decisions. It is a supervised learning algorithm that can be used for both classification and regression tasks.

**How it works**
**Splitting**: The tree splits the data into smaller subsets based on the values of the features.
**Structure**:

- 1. Root node: The top-most node of the tree.
- 2. Internal node: A node that has at least one child node.
- 3. Leaf node: A node that has no child nodes.
- 4. Branch: A connection between two nodes.
     **Type of Decision tree**:
- 1. Classification Tree: Used to categorize data into discrete classes.
- 2. Regression Tree: Used to predict continuous values.

**How to split**
**Classification**: Use Gini Impurity or Information Gain to split the data.
**Regression**: Use Mean Squared Error (MSE) or Mean Absolute Error (MAE) to split the data.

**Output**: In classification tree, the output is the class label. In regression tree, the output is the predicted value.

**Problem**

- **Overfitting**: Decision trees are prone to overfitting, especially when the tree is deep. This is because the tree can perfectly memorize the training data, but it will not generalize well to new data.

# Random Forest

**Core concept** Random Forest is an ensemble learning method that operates by constructing a multitude of decision trees at training time. For classification tasks, the output is the class selected by the majority of trees. For regression tasks, the output is the average prediction of all trees.

**How it works**
**Bagging**: Random Forest uses bagging (bootstrap aggregating) to train multiple decision trees on different subsets of the training data. This helps to reduce overfitting and improve the model's generalization performance.
**Structure**: Random Forest is a collection of decision trees. Each tree is trained on a different subset of the training data and features.
**Type of Random Forest**:

- **Classification Forest**: Used to categorize data into discrete classes.
- **Regression Forest**: Used to predict continuous values.

**Output**: In classification forest, the output is the class label. In regression forest, the output is the average prediction of all trees.

**Problem**

- **Overfitting**: Random Forest is prone to overfitting, especially when the tree is deep. This is because the tree can perfectly memorize the training data, but it will not generalize well to new data.

# Boosting

**Core concept** Boosting is an ensemble learning method that operates by constructing a multitude of decision trees at training time. For classification tasks, the output is the class selected by the majority of trees. For regression tasks, the output is the average prediction of all trees.

**How it works**
**Sequential learning**: Boosting trains decision trees sequentially, where each tree is trained on the errors of the previous trees. This helps to reduce overfitting and improve the model's generalization performance.
**Weight update**: Boosting updates the weights of the training data based on the errors of the previous trees. This helps to focus on the difficult-to-classify examples.
**Type of Boosting**:

- **AdaBoost**: Adaptive Boosting. It is a sequential learning algorithm that trains decision trees sequentially, where each tree is trained on the errors of the previous trees. This helps to reduce overfitting and improve the model's generalization performance.
- **Gradient Boosting**: Gradient Boosting. It is a sequential learning algorithm that trains decision trees sequentially, where each tree is trained on the errors of the previous trees. This helps to reduce overfitting and improve the model's generalization performance.
- **XGBoost**: Extreme Gradient Boosting. It is a gradient boosting algorithm that is optimized for performance and accuracy. It is a popular choice for machine learning competitions and real-world applications.

**Output**: In classification boosting, the output is the class label. In regression boosting, the output is the average prediction of all trees.

**Problem**

- **Overfitting**: Boosting is prone to overfitting, especially when the tree is deep. This is because the tree can perfectly memorize the training data, but it will not generalize well to new data.
