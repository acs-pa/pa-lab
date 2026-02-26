class MinStack:
    def __init__(self):
        # Stiva principala pentru stocarea elementelor
        self.st = []
        # Stiva auxiliara pentru stocarea elementelor minime
        self.minSt = []

    # Adauga elementul val in stiva.
    def push(self, val: int) -> None:
        self.st.append(val)

        # Daca stiva min este goala sau val este mai mic sau egal cu minimul curent,
        # il adauga in stiva min.
        if not self.minSt or val <= self.minSt[-1]:
            self.minSt.append(val)

    # Elimina elementul din varful stivei.
    def pop(self) -> None:
        if self.st[-1] == self.minSt[-1]:
            # Daca varful ambelor stive este acelasi, elimina si din stiva min.
            self.minSt.pop()
        self.st.pop()

    # Returneaza elementul din varful stivei.
    def top(self) -> int:
        return self.st[-1]

    # Returneaza elementul minim din stiva.
    def getMin(self) -> int:
        return self.minSt[-1]