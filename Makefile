make:
	gcc main.c -o main
	gcc gerar_testes.c -o gerar_testes

run:
	./gerar_testes
	./main

clean:
	rm -f main
	rm -f gerar_testes