pub struct BinarySearchTree {
    root: Option<Box<Node>>
}

struct Node {
    value: i32,
    count: u32,
    left_tree: Option<Box<Node>>,
    right_tree: Option<Box<Node>>,
}

impl BinarySearchTree {
    pub fn new() -> Self {
        Self { root: None, }
    }

    pub fn insert(&mut self, value: i32) {
        match &mut self.root {
            None => self.root = Some(Box::new(Node::new(value))), // If root is empty, creates one for the BST
            Some(t) => t.insert(value),
        }
    }

    pub fn search(&self, value: i32) -> bool {
        match &self.root {
            None => return false,
            Some(t) => return t.search(value),
        }
    }

    pub fn delete(&mut self, value: i32) -> bool {
        return delete_node_helper(&mut self.root, value);
    }
}

impl Node {
    fn new(value: i32) -> Self {
        Self {
            value,
            count: 1,
            left_tree: None,
            right_tree: None,
        }
    }

    fn insert(&mut self, value: i32) {
        // If value is less, moves left
        if value < self.value {
            match &mut self.left_tree {
                None => self.left_tree = Some(Box::new(Node::new(value))),
                Some(t) => t.insert(value),
            }
        }

        // If value is greater, moves right
        if value > self.value {
            match &mut self.right_tree {
                None => self.right_tree = Some(Box::new(Node::new(value))),
                Some(t) => t.insert(value),
            }
        }

        // If value is the same, increment count
        if value == self.value {
            self.count += 1;
        }
    }

    fn search(&self, value: i32) -> bool {
        if value == self.value {
            return true
        }
        
        if value < self.value {
            match &self.left_tree {
                None => return false,
                Some(t) => return t.search(value),
            }
        }

        if value > self.value {
            match &self.right_tree {
                None => return false,
                Some(t) => return t.search(value),
            }
        }

        false
    }
}

// Helper function to traverse through and delete nodes
fn delete_node_helper(link: &mut Option<Box<Node>>, value: i32) -> bool {
    let node = match link {
        None => return false,
        Some(node) => node,
    };

    if value < node.value {
        return delete_node_helper(&mut node.left_tree, value);
    }

    if value > node.value {
        return delete_node_helper(&mut node.right_tree, value);
    }

    //---------- Value found cases -----------//

    if node.count > 1 {
        node.count -= 1;
        return true;
    }

    // If node has no children
    if node.left_tree.is_none() && node.right_tree.is_none() {
        *link = None;
        return true;
    } 
    else if node.left_tree.is_some() && node.right_tree.is_none() { // If there is only a left child
        *link = node.left_tree.take();
        return true;
    }
    else if node.left_tree.is_none() && node.right_tree.is_some() { // If there is only a right child
        *link = node.right_tree.take();
        return true;
    }
    else { // If there are two children
        let successor = find_min(&mut node.right_tree);

        node.value = successor.value;
        node.count = successor.count;
        return true;
    }
}

// This function finds the minimum value from the specified starting point
fn find_min(link: &mut Option<Box<Node>>) -> Box<Node> {
    let node = link.as_mut().unwrap();

    if node.left_tree.is_none() {
        let mut min = link.take().unwrap();
        *link = min.right_tree.take();
        min
    }
    else {
        return find_min(&mut node.left_tree);
    }
}