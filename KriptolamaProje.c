#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_UZUNLUK 1000       

// --- EKRAN AYIRAC MACROSU ---
#define AYIRAC "--------------------------------------------------\n"

// --- YARDIMCI FONKSIYON: TAMPON TEMIZLEME ---
void tamponTemizle() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// --- 1. SEZAR ALGORITMASI ---
void sezarSifrele(char metin[], int anahtar) {
    char ch;
    printf("\n" AYIRAC);
    printf("[SONUC] Sezar Sifrelemesi (Anahtar: %d):\n>> ", anahtar);
    for(int i = 0; metin[i] != '\0'; ++i) {
        ch = metin[i];
        if(isalnum(ch)) {
            if(islower(ch)) ch = (ch - 'a' + anahtar) % 26 + 'a';
            else if(isupper(ch)) ch = (ch - 'A' + anahtar) % 26 + 'A';
        }
        printf("%c", ch);
    }
    printf("\n" AYIRAC);
}

void sezarCoz(char metin[], int anahtar) {
    char ch;
    printf("-> Anahtar %2d: ", anahtar); 
    for(int i = 0; metin[i] != '\0'; ++i) {
        ch = metin[i];
        if(isalnum(ch)) {
            if(islower(ch)) ch = (ch - 'a' - anahtar + 26) % 26 + 'a';
            else if(isupper(ch)) ch = (ch - 'A' - anahtar + 26) % 26 + 'A';
        }
        printf("%c", ch);
    }
    printf("\n");
}

// --- 2. ATBASH (AYNA) ALGORITMASI ---
// Binary yerine gelen yeni yontem.
// Simetrik oldugu icin sifreleme ve cozme aynidir.
void atbashIslemi(char metin[]) {
    char ch;
    printf("\n" AYIRAC);
    printf("[SONUC] Atbash (Ayna) Sifrelemesi:\n>> ");
    for(int i = 0; metin[i] != '\0'; ++i) {
        ch = metin[i];
        if(isalpha(ch)) {
            if(islower(ch)) {
                // 'a' (ilk) ile 'z' (son) arasindaki simetri
                ch = 'z' - (ch - 'a'); 
            }
            else if(isupper(ch)) {
                // 'A' ile 'Z' arasindaki simetri
                ch = 'Z' - (ch - 'A');
            }
        }
        printf("%c", ch);
    }
    printf("\n" AYIRAC);
}

// --- 3. VIGENERE ALGORITMASI ---
void vigenereIslemi(char metin[], char anahtar[], int sifreleMi) {
    int metinUzunluk = strlen(metin);
    int anahtarUzunluk = strlen(anahtar);
    int i, j;
    
    printf("\n" AYIRAC);
    if (sifreleMi) printf("[SONUC] Vigenere Sifreli Metin:\n>> ");
    else printf("[COZUM] Vigenere Cozulen Metin:\n>> ");

    for(i = 0, j = 0; i < metinUzunluk; ++i) {
        char c = metin[i];
        if(isalpha(c)) {
            char baslangic = isupper(c) ? 'A' : 'a';
            int kaydirma = toupper(anahtar[j % anahtarUzunluk]) - 'A';
            
            if (sifreleMi) printf("%c", (c - baslangic + kaydirma) % 26 + baslangic);
            else printf("%c", (c - baslangic - kaydirma + 26) % 26 + baslangic);
                
            j++; 
        } else {
            printf("%c", c); 
        }
    }
    printf("\n" AYIRAC);
}

// --- ARAYUZ FONKSIYONLARI ---
void baslikYazdir() {
    printf("\n");
    printf("==================================================\n");
    printf("||      GUVENLIK VE SIFRELEME SISTEMI v3.0      ||\n");
    printf("||         (Muhendislik Fakultesi Odevi)        ||\n");
    printf("==================================================\n");
}

void menuYazdir(char *baslik, char *secenekler[]) {
    printf("\n--- %s ---\n", baslik);
    for(int i = 0; secenekler[i] != NULL; i++) {
        printf("%d. %s\n", i + 1, secenekler[i]);
    }
    printf("0. Ana Menuye Don / Cikis\n");
    printf("Seciminiz: ");
}

// --- MAIN FONKSIYONU ---
int main() {
    int anaSecim, altSecim;
    char metin[MAX_UZUNLUK];
    int anahtarInt;
    char anahtarStr[100];

    // Menu metinleri - Binary gitti, Atbash geldi
    char *anaMenu[] = {"Sifrele (Encrypt)", "Sifre Coz (Decrypt)", NULL};
    char *sifrelemeMenu[] = {"Sezar (Kaydirma)", "Atbash (Ayna Simetri)", "Vigenere (Anahtar Kelime)", NULL};
    
    // Cozme menusu
    char *cozmeMenu[] = {"Sezar (Anahtari Biliyorum)", "Sezar (Sifreyi Kir / Brute Force)", "Atbash Cozumu", "Vigenere Cozumu", NULL};

    baslikYazdir();

    while(1) {
        menuYazdir("ANA MENU", anaMenu);
        
        if (scanf("%d", &anaSecim) != 1) {
            printf("\n[HATA] Lutfen gecerli bir sayi giriniz!\n");
            tamponTemizle();
            continue;
        }
        tamponTemizle();

        if (anaSecim == 0) {
            printf("\n[SISTEM] Programdan cikiliyor. Iyi calismalar!\n");
            break;
        }

        // --- SIFRELEME BOLUMU ---
        if (anaSecim == 1) { 
            menuYazdir("SIFRELEME ISLEMLERI", sifrelemeMenu);
            scanf("%d", &altSecim);
            tamponTemizle();
            if(altSecim == 0) continue;

            printf("\n[GIRIS] Sifrelenecek metni giriniz: ");
            fgets(metin, MAX_UZUNLUK, stdin);
            metin[strcspn(metin, "\n")] = 0;

            switch(altSecim) {
                case 1:
                    printf("[GIRIS] Kaydirma miktarini giriniz (Orn: 3): ");
                    scanf("%d", &anahtarInt);
                    sezarSifrele(metin, anahtarInt);
                    break;
                case 2:
                    // Atbash anahtar istemez, direk cevirir
                    atbashIslemi(metin);
                    break;
                case 3:
                    printf("[GIRIS] Anahtar kelimeyi giriniz (Orn: VATAN): ");
                    fgets(anahtarStr, 100, stdin);
                    anahtarStr[strcspn(anahtarStr, "\n")] = 0;
                    vigenereIslemi(metin, anahtarStr, 1);
                    break;
                default: printf("\n[HATA] Gecersiz secim!\n");
            }
        } 
        // --- COZME BOLUMU ---
        else if (anaSecim == 2) { 
            menuYazdir("COZME ISLEMLERI", cozmeMenu);
            scanf("%d", &altSecim);
            tamponTemizle();
            if(altSecim == 0) continue;

            printf("\n[GIRIS] Cozulecek metni giriniz: ");
            fgets(metin, MAX_UZUNLUK, stdin);
            metin[strcspn(metin, "\n")] = 0;

            if (altSecim == 1) {
                // Normal Sezar Cozumu
                printf("[GIRIS] Anahtar sayisi: ");
                scanf("%d", &anahtarInt);
                printf("\n" AYIRAC);
                printf("[COZUM] Tekli Cozum:\n");
                sezarCoz(metin, anahtarInt);
                printf(AYIRAC);
            } 
            else if (altSecim == 2) {
                // BRUTE FORCE (KABA KUVVET)
                printf("\n" AYIRAC);
                printf("[SISTEM] Kaba Kuvvet Saldirisi Baslatiliyor...\n");
                printf("Olasiliklar sirayla deneniyor:\n\n");
                for(int i = 1; i < 26; i++) {
                    sezarCoz(metin, i);
                }
                printf("\n[BILGI] Yukaridaki listeden anlamli olani seciniz.\n");
                printf(AYIRAC);
            }
            else if (altSecim == 3) {
                // Atbash simetrik oldugu icin ayni fonksiyon cozer
                printf("[BILGI] Atbash simetrik oldugu icin ayni islem uygulaniyor...\n");
                atbashIslemi(metin);
            }
            else if (altSecim == 4) {
                // Vigenere Cozumu
                printf("[GIRIS] Anahtar kelime: ");
                fgets(anahtarStr, 100, stdin);
                anahtarStr[strcspn(anahtarStr, "\n")] = 0;
                vigenereIslemi(metin, anahtarStr, 0); 
            } else {
                printf("\n[HATA] Gecersiz secim!\n");
            }
        }
        else {
            printf("\n[HATA] Gecersiz secim! Lutfen tekrar deneyin.\n");
        }
    }
    return 0;
}