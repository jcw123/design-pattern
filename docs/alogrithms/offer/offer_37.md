## 序列化二叉树

### 题目描述

请实现两个函数，分别用来序列化和反序列化二叉树。

你需要设计一个算法来实现二叉树的序列化与反序列化。这里不限定你的序列 / 反序列化算法执行逻辑，你只需要保证一个二叉树可以被序列化为一个字符串并且将这个字符串反序列化为原始的树结构。

### 解题思路

**我的思路**
本题的要求是将二叉树进行序列化然后再反序列化，我的初始想法是构建二叉树的前序遍历和中序遍历，构建的过程中把空节点都忽略了，如果有值相同得节点，就没法通过前序遍历和中序遍历恢复二叉树了，结果就卡在这里了。

**官方的思路**

- bfs遍历
  通过bfs方式构建序列化字符串，然后再经过bfs恢复序列化字符串。其中的关键点是如果一个节点不为空，需要将此节点的左右子树都进行序列化，如果左右子树某一个为空，需要用一个空节点的值进行表示。

- dfs
  dfs序列化合反序列化的关键点是如果一个节点的左子树或者又子树为空，也用一个特殊的节点进行表示

### 代码

**方法一**
> bfs

```java
/**
 * Definition for a binary tree node.
 * public class TreeNode {
 *     int val;
 *     TreeNode left;
 *     TreeNode right;
 *     TreeNode(int x) { val = x; }
 * }
 */
public class Codec {

    private static final TreeNode EMPTY_NODE = new TreeNode(Integer.MAX_VALUE);

    // Encodes a tree to a single string.
    public String serialize(TreeNode root) {
        if(root == null) {
            return "";
        }
        Queue<TreeNode> queue = new LinkedList<>();
        queue.offer(root);
        StringBuilder sb = new StringBuilder();
        while(!queue.isEmpty()) {
            TreeNode p = queue.poll();
            sb.append(p.val + "_");
            if(p != EMPTY_NODE) {
                queue.offer(p.left != null ? p.left : EMPTY_NODE);
                queue.offer(p.right != null ? p.right : EMPTY_NODE);
            }
        }
        return sb.toString();
    }

    // Decodes your encoded data to tree.
    public TreeNode deserialize(String data) {
        if("".equals(data)) {
            return null;
        }
        String[] arr = data.split("_");
        TreeNode root = new TreeNode(Integer.parseInt(arr[0]));
        Queue<TreeNode> queue = new LinkedList<>();
        queue.offer(root);
        TreeNode p;
        for(int i = 1; i < arr.length - 1; i += 2) {
            p = queue.poll();
            int leftV = Integer.parseInt(arr[i]);
            int rightV = Integer.parseInt(arr[i + 1]);
            if(leftV != Integer.MAX_VALUE) {
                p.left = new TreeNode(leftV);
                queue.offer(p.left);
            }
            if(rightV != Integer.MAX_VALUE) {
                p.right = new TreeNode(rightV);
                queue.offer(p.right);
            }
        }
        return root;
    }
}

// Your Codec object will be instantiated and called as such:
// Codec codec = new Codec();
// codec.deserialize(codec.serialize(root));
```

**方法二**
> dfs

```java
/**
 * Definition for a binary tree node.
 * public class TreeNode {
 *     int val;
 *     TreeNode left;
 *     TreeNode right;
 *     TreeNode(int x) { val = x; }
 * }
 */
public class Codec {

    // Encodes a tree to a single string.
    public String serialize(TreeNode root) {
        if(root == null) {
            return "A";
        }
        return String.join(",", String.valueOf(root.val), serialize(root.left), serialize(root.right));
    }

    // Decodes your encoded data to tree.
    public TreeNode deserialize(String data) {
        Queue<String> queue = new LinkedList<>();
        for(String s : data.split(",")) {
            queue.offer(s);
        }
        return buildTree(queue);
    }

    private TreeNode buildTree(Queue<String> queue) {
            String s = queue.poll();
            if("A".equals(s)) {
                return null;
            }
            TreeNode root = new TreeNode(Integer.parseInt(s));
            root.left = buildTree(queue);
            root.right = buildTree(queue);
            return root;
        }
}

// Your Codec object will be instantiated and called as such:
// Codec codec = new Codec();
// codec.deserialize(codec.serialize(root));
```

### 复杂度分析

- 时间复杂度O(n):n为节点的个数；
- 空间复杂度O(n):n为节点的个数；

### 核心点
1. 对树本质上有深刻的理解，熟悉bfs和dfs遍历的关键点；

### 思考

对于树或者图，我掌握的还是很不牢固，这部分需要加强练习，针对于树，涉及到树的遍历，递推的应用需要加强；针对于图涉及图的构建、图的遍历、最小生成树、最短路径、拓扑排序都需要进行加强；