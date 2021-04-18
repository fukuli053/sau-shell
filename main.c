#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int QUIT = 0;
char *komutlar_shell[] = {"help", "quit"};

int komutSayisi()
{
  return sizeof(komutlar_shell) / sizeof(char *);
}

int cikisFonksiyonu()
{
  QUIT = 1;
  int cikis;
  while (!waitpid(-1, &cikis, WNOHANG))
  {
  }
  exit(0);
  return 0;
}

int yardimFonksiyonu(char **args)
{
  int i;
  printf("****Isletim Sistemleri Odevi******\n");
  printf("Furkan Ergun\n");
  printf("Hacı Karadag\n");
  printf("Yusuf Ensar Kurt\n");
  printf("Muhammed Selim Yildiz\n");
  printf("Samet Emin Sevil\n");

  printf("EK KOMUTLAR\n");

  for (i = 0; i < komutSayisi(); i++)
  {
    printf("  %s\n", komutlar_shell[i]);
  }

  return 1;
}

int (*shell_komutlari[])(char **) = {&yardimFonksiyonu, &cikisFonksiyonu};

char *komutOku(void)
{
  int karakterSayisi = 512;
  int position = 0;
  char *metin = malloc(sizeof(char) * karakterSayisi);
  int c;

  if (!metin)
  {
    fprintf(stderr, "Bellek Hatasi\n");
    exit(EXIT_FAILURE);
  }

  while (1)
  {
    c = getchar();

    if (c == EOF)
    {
      exit(EXIT_SUCCESS);
    }
    else if (c == '\n')
    {
      if (position >= karakterSayisi)
      {
        return NULL;
      }
      metin[position] = '\0';
      return metin;
    }
    else
    {
      if (position < karakterSayisi)
      {
        metin[position] = c;
      }
    }
    position++;
  }
}

char *trimwhitespace(char *str)
{
  char *end;

  while (isspace((unsigned char)*str))
    str++;

  if (*str == 0)
    return str;

  end = str + strlen(str) - 1;
  while (end > str && isspace((unsigned char)*end))
    end--;

  end[1] = '\0';

  return str;
}

char **satiriParcala(char *line)
{
  char **komutlar = (char **)malloc(sizeof(char *) * 64);
  int sayac = 0;
  char *komut = strtok(line, ";");
  while (komut != NULL)
  {
    komutlar[sayac] = trimwhitespace(komut);
    komut = strtok(NULL, ";");
    sayac++;
  }
  return komutlar;
}

void komutCalistir(char **komut)
{
  pid_t pid = fork();
  if (pid == 0)
  {
    if (execvp(komut[0], komut))
    {
      perror("SAU-SHELL:");
    }
    exit(EXIT_FAILURE);
  }
  else if (pid < 0)
  {
    perror("SAU-SHELL: ");
  }
  else
  {
    wait(NULL);
  }
}

int komutlariCalistir(char **komutlar)
{

  int j = 0;

  if (komutlar == NULL)
  {
    return 0;
  }

  for (int i = 0; komutlar[i] != NULL; i++)
  {
    for (j = 0; j < komutSayisi(); j++)
    {
      if (strcmp(komutlar[i], komutlar_shell[j]) == 0)
        return (*shell_komutlari[j])(komutlar);
    }

    char **kelimeListesi = (char **)malloc(sizeof(char *) * 64);
    char *kelime = strtok(komutlar[i], " ");

    for (j = 0; kelime != NULL; j++)
    {
      kelimeListesi[j] = kelime;
      kelime = strtok(NULL, " ");
    }

    komutCalistir(kelimeListesi);
    free(kelimeListesi);
  }
}

//Batch icin dosya okuma islemi
int dosyaOku(char filename[100])
{
  printf("Batch modu. Dosya açılıyor: %s", filename);
  FILE *fptr;
  char line[200];
  char **args;
  fptr = fopen(filename, "r");
  if (fptr == NULL)
  {
    printf("\nDosya açılamadı.");
    return 1;
  }
  else
  {
    printf("\nDosya açıldı. Parçalanıyor.\n");
    while (fgets(line, sizeof(line), fptr) != NULL)
    {
      printf("\n%s\n\n", line);
      args = satiriParcala(line);
      komutlariCalistir(args);
    }
  }
  free(args);
  fclose(fptr);
  return 1;
}

//CTRL tusuna basildiginda cikmamasi icin
void controlTusu(int number)
{
  if (number == SIGINT)
  {
  }
  else if (number == SIGQUIT)
  {
  }
  else if (number == SIGTSTP)
  {
  }
}

int prompt()
{
  char *line;
  char **args;
  while (QUIT == 0)
  {
    //CTRL durumlarında çıkmaması için (CTRL+D haric)
    signal(SIGINT, controlTusu);
    signal(SIGTSTP, controlTusu);
    signal(SIGQUIT, controlTusu);

    printf("SAU-SHELL> ");

    line = komutOku();

    if (line == NULL)
    {
      printf("Girilebilecek karakter sayisini astiniz. \n");
    }
    else
    {
      args = satiriParcala(line);
      komutlariCalistir(args);

      free(line);
      free(args);
    }
  }
  return 1;
}

int main(int argc, char **argv)
{
  if (argc == 1)
    prompt();
  else if (argc == 2)
    dosyaOku(argv[1]);
  else
    printf("\nGeçersiz sayıda parametre girildi.\n");

  return EXIT_SUCCESS;
}