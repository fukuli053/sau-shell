Proje Adı: C ile Shell(Kabuk) Projesi

Grup Elemanları: 
Furkan Ergün - b181210091,
Hacı Karadağ - b181210013,
Yusuf Ensar Kurt - b181210115,
Muhammed Selim Yıldız - b181210073,
Samet Emin Sevil - b181210106,

2. Tasarıma Genel Bakış:
	Proje toplu ve etkileşimli modda çalışabilen bir kabuk yapısıdır. İnteraktif mod kullanıcının komutları prompt ekranına yazmasıyla
beraber entera basınca çalışır. Batch mod ise kullanıcının programı çalıştırırken yanında parametre olarak bir dosya vermesi 
halinde dosyanın içerisindeki komutları çalıştırabilir.

	Kodumuz etkileşimli modda çalıştığı anda kullanıcıdan 512 karakteri aşmayan komut veya komutlar girmesini bekler. 
Eğer komutun karakterlerinin sayısı 512 den küçükse bunu kontrol ederek çalıştırma işlemini başlatıyoruz. Komut ';'
ile ayrılmış bir komut ise önceliğimiz bu komut satırını ';' ile bölmek. Bunun için strtok fonksiyonunu kullandık.
';' e böldükten sonra elimizde oluşan komutun başındaki ve sonundaki gereksiz boşlukları programımız düzgün çalışsın diye
boşlukları silen fonksiyonumuzu çalıştırıyoruz. Sonrasında ise elde ettiğimiz komutu çalıştırıp varsa diğer ';' komutuna geçiyoruz.
Eğer tek komut varsa direkt olarak bir process ile çalıştırıyoruz. Eğer birden fazla komut varsa parallelliği oluşturmak 
adına ';' ile bölüp elde ettiğimiz komutlar için döngü ile adedince process oluşturuyoruz ve her bir processe gerekli komutu
atayarak parallelliği sağlıyoruz. 
	Kodumuz toplu modda çalışırken de anlatılan işlemleri uyguluyor fakat kod çalıştırılırken önce parametre olarak gönderilen dosya
fonksiyonumuz tarafından okunuyor, her bir satırı okuyup ';' varsa parçalıyor ve çalıştırıyor. Her iki modda da satır içinde quit
komutu görüldüğü an uygulama tüm processleri öldürüp çıkış yapılıyor.

3. Özel Durumlar:
	-Komut satırı boş ise bunu kontrol edip hiçbir işlem yapmamasını sağlıyoruz.
    -Yanlış bir komut girilmesi durumunda program çökmeden devam eder.
    -"mkdir a ;;; ;;; ls -l;;;" gibi durumlarda komutları gördüğü yerde çalıştırır ve çökmez. Bunun için strok ile bölerken kontrol ediyoruz
    böylece olası hataların önüne geçilmiş oluyor.
    -512 karakterden fazla veri girilmesi durumunda program fazla karakter girildiğini söyleyerek çalışmaya devam eder.
    -Sadece CTRL-D tuşunda veya "quit" komutunda programdan çıkılması için sinyal kontrolleri eklendi.

4. Bilinen Hatalar veya Sorunlar:
	Gözlemlenen bir hata bulunmamakta.
