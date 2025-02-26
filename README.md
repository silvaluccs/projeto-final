# Sistema de Gerenciamento de Reservatório de Água

## Visão Geral
Este projeto implementa um sistema embarcado para monitoramento e controle de um reservatório de água utilizando um Raspberry Pi Pico. O sistema permite interação com o usuário através de um display OLED, um joystick e botões, além de utilizar LEDs para indicar o status do reservatório.

## Funcionalidades
- **Monitoramento do nível da água** via sensores (a serem adicionados).
- **Controle do reservatório** através de um menu interativo.
- **Interface amigável** utilizando um display OLED.
- **Feedback visual** por meio de LEDs para indicar diferentes estados.
- **Interação com joystick e botões** para navegação no menu.

## Componentes Utilizados
- **Microcontrolador**: Raspberry Pi Pico
- **Display**: OLED SSD1306
- **Sensores**: (a definir, ex. sensores de nível de água)
- **Joystick**: Para controle do menu
- **Botões**: Entrada adicional do usuário
- **LEDs**: Indicadores visuais do estado do sistema

## Estrutura do Código
O projeto está organizado nos seguintes arquivos e diretórios:

- `main.c`: Arquivo principal do programa.
- `includes/`: Contém arquivos de cabeçalho (.h) com definições de funções e macros.
- `src/`: Contém os arquivos de implementação (.c) do sistema.
- `CMakeLists.txt`: Configuração para compilação com CMake.
- `pico_sdk_import.cmake`: Importação do SDK do Raspberry Pi Pico.

## Como Compilar e Executar
### Requisitos
- Raspberry Pi Pico
- SDK do Raspberry Pi Pico instalado
- CMake e um compilador compatível (ex. GCC para ARM)

## Uso do Sistema
- Utilize o **joystick** para navegar pelo menu.
- Pressione os **botões** para confirmar seleções.
- Os **LEDs** indicam estados do sistema (exemplo: verde para normal, vermelho para alerta).
- O **display OLED** mostra informações como nível de água e opções do menu.

## Melhorias Futuras
- Integração com sensores reais de nível de água.
- Adição de comunicação remota (ex. Wi-Fi ou Bluetooth).
- Implementação de alertas sonoros.

## Licença
Este projeto está sob a licença MIT. Sinta-se à vontade para usar e modificar conforme necessário.

