# LILYGO T5 V2.3 versiyonu kodlanarak geliştirilen yaka kartı uygulaması

#### Amaç
Bu ürün; bu ürünü kullanan temizlik, güvenlik vb görevliler, bulunması gereken veya temizlemesi gereken yerlerde işlerini yaparken, bluetooth sinyali yayar.

#### Özellikleri
1. Üzerindeki 33 numaralı pin, Bataryanın Vin girişne bağlanmıştır. Bu sayede bataryanın durumunu ölçecek şekilde kodlanmıştır.
2. Belirli zaman aralıklarında BLE Beacon yapmaktadır.
3. Kullanılmadığı zamanlarda Deep Sleep ile uykuya geçmektedir.
4. Şarj olurken, şarj durumunu algılayabilmektedir.
5. IP adresi kullanılarak HTTP ile yaka kartına isim verilebilmektedir.
6. Uzaktan kodlanabilmektedir. OTA özelliği eklenmiştir.


#### Kullanım alanları daha detaylı açıklama
Bu ürünü bir temizlik görevi icra eden meslek ile örneklendirecek olursak;

Yaka kartını satın alan firma kendi Wifi ağına bağladıktan sonra, yaka kartını takacak olan görevliye cihazın IP adresini vermesi yeterlidir.

Ürünün IP adresi bilgisini edinen görevli telefonu ile ürünün aynı Wifi ağına bağlı olduğunu kontrol ettikten sonra, bir web tarayıcısına kendisine verilen ip adresini yazar.

Ardından önüne gelen basit HTML sitesinde ismini ve görevini yazarak gönder butonuna tıklar.

Ürün gelen bilgileri alarak ekranda göstermeye başlar.

Görevli yaka kartını takarak temizlenmesi gereken noktaya gider.

Bu noktada bulunan sinyal algılayıcı ile temizlik görevlisinin taktığı üründen yayılan BLE Beacon yayını eşleşerek temizlik görevlisinin orada bulunduğunu raporlar.

Bu rapor içerisinde Temizlik görevlisinin bulunduğu süre, gerekirse alan içindeli konum bilgileri bulunabilir.

Görev tamamamlandıktan sonra yerinden ayrılan görevlinin BLE Beacon yayınıda uzaklaşacağı için sinyal kesilir ve rapora görevlilin ayrıldığı saat yazılır.



### Sonuç
Buradaki sonuç belirli noktalarda RFID okutucuyu okutmayı unutan veya temizlik görevlisinin o konumda ne kadar süre bulunduğunu nereleri temizlediğini görmek isteyen firmalara çözüm olmaktadır.