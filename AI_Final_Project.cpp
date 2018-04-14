// Amir Afridi
// Chris Amituanai
// Justin Sanchez

// Classification Problem
// This evaluates properties of the book and finds what gives
// the highest gain to find whether the book has positive
// or negative reviews

#include <iostream>
#include <list>
#include <string>
#include <iterator>
#include <math.h>
#include <cmath>
#include <queue>

using namespace std;

class Book {
public:
  bool binding; // 0 = soft     | 1 = hard
  bool length;  // 0 = short    | 1 = long
  bool color;   // 0 = b/w      | 1 = color
  bool review;  // 0 = negative | 1 = positive

  Book(bool a, bool b, bool c, bool d) {
    this->binding = a;
    this->length = b;
    this->color = c;
    this->review = d;
  }

  string ToString () {
    string str;
    str.append("binding: ").append((binding ? "Hard" : "Soft"));
    str.append(" | length: ").append((length ? "Long" : "Short"));
    str.append(" | color: ").append((color ? "Color" : "Black/White"));
    str.append(" | review: ").append((review ? "Positive" : "Negative"));

    return (str);
  }
};

class TreeNode {
  public:
     bool PropertiesEvaluated[3]; // binding | length | color
     list<Book> listOfBooks; // list of books that fall to that node in the tree
     TreeNode* leftNode;
     TreeNode* rightNode;
     string propertyEvaluated;
     int finalReview;           //-1 for negative | 0 for neither | 1 for positive

  TreeNode () {
    this->PropertiesEvaluated[0] = 0;
    this->PropertiesEvaluated[1] = 0;
    this->PropertiesEvaluated[2] = 0;
    this->listOfBooks = list<Book>();
    this->leftNode = NULL;
    this->rightNode = NULL;
    this->propertyEvaluated = "";
    this->finalReview = 0;
  }

  TreeNode (list<Book> books) {
    this->PropertiesEvaluated[0] = 0;
    this->PropertiesEvaluated[1] = 0;
    this->PropertiesEvaluated[2] = 0;
    this->listOfBooks = books;
    this->leftNode = NULL;
    this->rightNode = NULL;
    this->propertyEvaluated = "";
    this->finalReview = 0;
  }

};

float logBase2(float x) {
  return (log(x) / log(2.0));
}

float IFunction (float countP, float countN) {
  if(countP == 0 || countN == 0) {
    return 0;
  }
  float total = countP + countN;
  return (-1) * ((countP/total) * (logBase2(countP/total)) + (countN/total) * (logBase2(countN/total)));
}

float findBindingGains (list<Book> books, float i) {
  float bindingGains;
  float countPP = 0; //positive on property checking / positive on review
  float countPN = 0; //positive on property checking / negative on review
  float countNP = 0; //negative on property checking / positive on review
  float countNN = 0; //negative on property checking / negative on review
  float count = 0;
  float hardBinding = 0;
  float softBinding = 0;
  list<Book>::iterator it;
  for(it = books.begin(); it != books.end(); it++) {
    if(it->binding) {
      hardBinding++;
      if(it->review) {
        countPP++;
      } else {
        countPN++;
      }
    } else {
      softBinding++;
      if(it->review) {
        countNP++;
      } else {
        countNN++;
      }
    }
    count++;
  }
  bindingGains = (i - ((hardBinding/count)*IFunction(countPP, countPN) + (softBinding/count)*IFunction(countNP, countNN)));
  cout << "Binding Gains = " << bindingGains << endl;
  return bindingGains;
}

float findLengthGains(list<Book> books, float i) {
  float lengthGains;
  float countPP = 0; //positive on property checking / positive on review
  float countPN = 0; //positive on property checking / negative on review
  float countNP = 0; //negative on property checking / positive on review
  float countNN = 0; //negative on property checking / negative on review
  float count = 0;
  float shortLength = 0;
  float longLength = 0;
  list<Book>::iterator it;
  for(it = books.begin(); it != books.end(); it++) {
    if(it->length) {
      longLength++;
      if(it->review) {
        countPP++;
      } else {
        countPN++;
      }
    } else {
      shortLength++;
      if(it->review) {
        countNP++;
      } else {
        countNN++;
      }
    }
    count++;
  }
  lengthGains = (i - ((longLength/count)*IFunction(countPP, countPN) + (shortLength/count)*IFunction(countNP, countNN)));
  cout << "Length Gains = " << lengthGains << endl;
  return lengthGains;
}

float findColorGains(list<Book> books, float i) {
  float colorGains;
  float countPP = 0; //positive on property checking / positive on review
  float countPN = 0; //positive on property checking / negative on review
  float countNP = 0; //negative on property checking / positive on review
  float countNN = 0; //negative on property checking / negative on review
  float count = 0;
  float colored = 0;
  float noColor = 0;
  list<Book>::iterator it;
  for(it = books.begin(); it != books.end(); it++) {
    if(it->color) {
      colored++;
      if(it->review) {
        countPP++;
      } else {
        countPN++;
      }
    } else {
      noColor++;
      if(it->review) {
        countNP++;
      } else {
        countNN++;
      }
    }
    count++;
  }
  colorGains = (i - ((colored/count)*IFunction(countPP, countPN) + (noColor/count)*IFunction(countNP, countNN)));
  cout << "Color Gains = " << colorGains << endl;
  return colorGains;
}



float findClassificationI(list<Book> books) {
  float countP = 0.0;
  float countN = 0.0;
  float count = 0.0;
  float I;
  list<Book>::iterator it;
  for(it = books.begin(); it != books.end(); it++) {
    it->review ? countP++ : countN++;
    count++;
  }

  I = IFunction(countP, countN);
  cout << "I = " << I << endl;

  return I;
}

void PrintTreeNode (TreeNode t) {
  cout << "print tree node called" << endl;
  list<Book>::iterator it;
  for(it=t.listOfBooks.begin(); it!=t.listOfBooks.end(); it++) {
    cout << it->ToString() << endl;
  }
}

void CheckBooksReview (TreeNode t, bool binding, bool length, bool color) {
  cout << "check books review called: " << endl;
  cout << "Node being recursively called on" << endl;
  PrintTreeNode(t);
  list<Book>::iterator it;
  bool reviewFlag = t.listOfBooks.begin()->review;
  bool checkFlag = 0;
  for(it = t.listOfBooks.begin(); it != t.listOfBooks.end(); it++) {
    if (it->review != reviewFlag) {
      checkFlag = 1;
    }
  }
  if (checkFlag) {
    if(t.propertyEvaluated == "BINDING") {
      binding ? CheckBooksReview(*t.leftNode, binding, length, color) : CheckBooksReview(*t.rightNode, binding, length, color);
    } else if (t.propertyEvaluated == "LENGTH") {
      length ? CheckBooksReview(*t.leftNode, binding, length, color) : CheckBooksReview(*t.rightNode, binding, length, color);
    } else { // t.propertyEvaluated == "COLOR"
      color ? CheckBooksReview(*t.leftNode, binding, length, color) : CheckBooksReview(*t.rightNode, binding, length, color);
    }
  } else {
    cout << "Book review is: " << (reviewFlag ? "GOOD" : "BAD") << endl;
  }
}

void TestBooks (TreeNode *t) {
  cout << "Create a book to test: \n";
  bool a, b, c, d;
  cout << "Enter 1 for hard bound book | 0 for soft bound booK: ";
  cin >> a;
  cout << "Enter 1 for long book | 0 for short book: ";
  cin >> b;
  cout << "Enter 1 for color book | 0 for black/white book: ";
  cin >> c;

  CheckBooksReview(*t, a, b, c);

}

int main () {
  int a;
  list<Book> books;
  list<Book> leftBooks, rightBooks;

  float mainI, bindingGains, lengthGains, colorGains;
  int selection; // 0 = binding | 1 = length | 2 = color

  // setup list of books
  books.push_back(Book(1, 1, 0, 1));
  books.push_back(Book(0, 1, 0, 1));
  books.push_back(Book(0, 0, 0, 0));
  books.push_back(Book(1, 0, 1, 1));
  books.push_back(Book(1, 0, 1, 1));
  books.push_back(Book(0, 0, 0, 0));
  books.push_back(Book(1, 1, 1, 1));
  books.push_back(Book(0, 0, 1, 0));

  TreeNode mainTreeNode = TreeNode(books);
  TreeNode rNode[8];
  TreeNode lNode[8];
  queue<TreeNode*> q;
  q.push(&mainTreeNode);

  cout << "root node\n";
  PrintTreeNode(mainTreeNode);

  int i = 0;
  while(!q.empty()) {
    PrintTreeNode(q.front()->listOfBooks);
    leftBooks = list<Book>();
    rightBooks = list<Book>();

    list<Book>::iterator it;

    mainI = findClassificationI(q.front()->listOfBooks);

    if(!q.front()->PropertiesEvaluated[0]) {
      bindingGains = findBindingGains(books, mainI);
    } else {
      bindingGains = -100;
    }
    if(!q.front()->PropertiesEvaluated[1]) {
      lengthGains = findLengthGains(books, mainI);
    } else {
      lengthGains = -100;
    }
    if(!q.front()->PropertiesEvaluated[2]) {
      colorGains = findColorGains(books, mainI);
    } else {
      colorGains = -100;
    }


    if(bindingGains == lengthGains && lengthGains == colorGains && colorGains == -100) {
      cout << "All Properties Evaluated";
    }
//BINDING---------------------------------------------------------------------------------------
    else if(bindingGains >= lengthGains && bindingGains >= colorGains) {
      selection = 0;
      q.front()->propertyEvaluated = "BINDING";
      list<Book>::iterator it2;
      for(it2 = q.front()->listOfBooks.begin(); it2 != q.front()->listOfBooks.end(); it2++) {
        it2->binding ? leftBooks.push_back(*it2) : rightBooks.push_back(*it2); //if hardBinding add to left | else add to right
      }
      lNode[i] = TreeNode(leftBooks);
      rNode[i] = TreeNode(rightBooks);
      q.front()->leftNode = &lNode[i];
      q.front()->rightNode = &rNode[i];
      cout << "left node\n";
      PrintTreeNode(*q.front()->leftNode);
      cout << "right node\n";
      PrintTreeNode(*q.front()->rightNode);
      q.front()->leftNode->PropertiesEvaluated[2] = q.front()->PropertiesEvaluated[2];
      q.front()->rightNode->PropertiesEvaluated[2] = q.front()->PropertiesEvaluated[2];
      q.front()->leftNode->PropertiesEvaluated[1] = q.front()->PropertiesEvaluated[1];
      q.front()->rightNode->PropertiesEvaluated[1] = q.front()->PropertiesEvaluated[1];
      q.front()->leftNode->PropertiesEvaluated[0] = 1;
      q.front()->rightNode->PropertiesEvaluated[0] = 1;
      bool bookflag = leftBooks.begin()->review;
      bool addFlag = 0;
      for(it = leftBooks.begin(); it != leftBooks.end(); it++) {
        if(it->review != bookflag) {
          addFlag = 1;
        }
      }
      if(addFlag) {
        q.push(q.front()->leftNode);
      } else {
        q.front()->leftNode->finalReview = bookflag;
      }
      bookflag = rightBooks.begin()->review;
      addFlag = 0;
      for(it = rightBooks.begin(); it != rightBooks.end(); it++) {
        if(it->review != bookflag) {
          addFlag = 1;
        }
      }
      if(addFlag) {
        q.push(q.front()->rightNode);
      } else {
        q.front()->rightNode->finalReview = bookflag;
      }
//BINDING---------------------------------------------------------------------------------------
//LENGTH---------------------------------------------------------------------------------------
    } else if (lengthGains >= bindingGains && lengthGains >= colorGains) {
      selection = 1;
      q.front()->propertyEvaluated = "LENGTH";
      list<Book>::iterator it2;
      for(it2 = q.front()->listOfBooks.begin(); it2 != q.front()->listOfBooks.end(); it2++) {
        it2->length ? leftBooks.push_back(*it2) : rightBooks.push_back(*it2); //if long add to left | else add to right
      }
      lNode[i] = TreeNode(leftBooks);
      rNode[i] = TreeNode(rightBooks);
      cout << "left node\n";
      PrintTreeNode(lNode[i]);
      cout << "right node\n";
      PrintTreeNode(rNode[i]);
      lNode[i].PropertiesEvaluated[0] = q.front()->PropertiesEvaluated[0];
      rNode[i].PropertiesEvaluated[0] = q.front()->PropertiesEvaluated[0];
      lNode[i].PropertiesEvaluated[2] = q.front()->PropertiesEvaluated[2];
      rNode[i].PropertiesEvaluated[2] = q.front()->PropertiesEvaluated[2];
      lNode[i].PropertiesEvaluated[1] = 1;
      rNode[i].PropertiesEvaluated[1] = 1;

      q.front()->leftNode = &lNode[i];
      q.front()->rightNode = &rNode[i];
      bool bookflag = leftBooks.begin()->review;
      bool addFlag = 0;
      for(it = leftBooks.begin(); it != leftBooks.end(); it++) {
        if(it->review != bookflag) {
          addFlag = 1;
        }
      }
      if(addFlag) {
        q.push(q.front()->leftNode);
      } else {
        q.front()->leftNode->finalReview = bookflag;
      }
      bookflag = rightBooks.begin()->review;
      addFlag = 0;
      for(it = rightBooks.begin(); it != rightBooks.end(); it++) {
        if(it->review != bookflag) {
          addFlag = 1;
        }
      }
      if(addFlag) {
        q.push(q.front()->rightNode);
      } else {
        q.front()->rightNode->finalReview = bookflag;
      }
      PrintTreeNode(*mainTreeNode.leftNode);
//LENGTH---------------------------------------------------------------------------------------
//COLOR---------------------------------------------------------------------------------------
    } else {
      selection = 2;
      q.front()->propertyEvaluated = "COLOR";
      list<Book>::iterator it2;
      for(it2 = q.front()->listOfBooks.begin(); it2 != q.front()->listOfBooks.end(); it2++) {
        it2->color ? leftBooks.push_back(*it2) : rightBooks.push_back(*it2); //if colored add to left | else add to right
      }
      lNode[i] = TreeNode(leftBooks);
      rNode[i] = TreeNode(rightBooks);
      cout << "left node\n";
      PrintTreeNode(lNode[i]);
      cout << "right node\n";
      PrintTreeNode(rNode[i]);
      lNode[i].PropertiesEvaluated[0] = q.front()->PropertiesEvaluated[0];
      rNode[i].PropertiesEvaluated[0] = q.front()->PropertiesEvaluated[0];
      lNode[i].PropertiesEvaluated[1] = q.front()->PropertiesEvaluated[1];
      rNode[i].PropertiesEvaluated[1] = q.front()->PropertiesEvaluated[1];
      lNode[i].PropertiesEvaluated[2] = 1;
      rNode[i].PropertiesEvaluated[2] = 1;

      q.front()->leftNode = &lNode[i];
      q.front()->rightNode = &rNode[i];
      bool bookflag = leftBooks.begin()->review;
      bool addFlag = 0;
      for(it = leftBooks.begin(); it != leftBooks.end(); it++) {
        if(it->review != bookflag) {
          addFlag = 1;
        }
      }
      if(addFlag) {
        q.push(&lNode[i]);
      } else {
        q.front()->leftNode->finalReview = bookflag;
      }
      bookflag = rightBooks.begin()->review;
      addFlag = 0;
      for(it = rightBooks.begin(); it != rightBooks.end(); it++) {
        if(it->review != bookflag) {
          addFlag = 1;
        }
      }
      if(addFlag) {
        q.push(&rNode[i]);
      } else {
        q.front()->rightNode->finalReview = bookflag;
      }
      PrintTreeNode(*mainTreeNode.leftNode);
    }
    cin >> a;
//COLOR---------------------------------------------------------------------------------------
    q.pop();
    i++;
  }

  TestBooks(&mainTreeNode);

  return 0;
}
