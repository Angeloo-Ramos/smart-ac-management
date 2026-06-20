#ifndef MENU_H
#define MENU_H

class Menu {
  public:
    void mostrarMenu();
    void execOpcao(int option);

    void mostrarHora();
    void mostrarData();

    int lerInteiro(const char* mensagem);

    void ajustarHora();
    void ajustarData();

    void limparMonitor();
};

#endif