import re
class Solution:
    def simplifyPath(self, path: str) -> str:
        lista = re.split('/+', path)
        print(lista)

        stek = []
        for x in lista:
            if(x == ".." and stek):
                stek.pop()
            elif(x != "" and x != "." and x != ".."):
                stek.append(x)

        res = "" 
        for x in stek:
            res = res + '/' + x
        if(res == ""):
            return "/"
        return res
