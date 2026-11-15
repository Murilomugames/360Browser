
# 360Browser — Arquitetura

## Plataforma
- Xbox 360 RGH/JTAG
- Wi-Fi do próprio console
- Executável XEX
- SDK: XSDK

## Componentes
- Interface gráfica: C
- Rede: sockets do XSDK
- HTTP/HTTPS: curl-xenon
- Leitura HTML: parser próprio
- Renderização: GPU Xenos

## Objetivo
Navegar diretamente pela internet,
sem servidor intermediário na casa do usuário.

## Desenvolvimento
1. Testar conexão de rede.
2. Fazer uma requisição HTTP/HTTPS.
3. Ler o HTML recebido.
4. Renderizar textos e links.
5. Implementar imagens e favoritos.
