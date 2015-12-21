/*  1:   */ package common;
/*  2:   */ 
/*  3:   */ import java.util.Map.Entry;
/*  4:   */ 
/*  5:   */ class Helper
/*  6:   */ {
/*  7:   */   static <K, T> MapView.EntryView<K, T> makeEntryView(Map.Entry<K, T> src)
/*  8:   */   {
/*  9:14 */     new MapView.EntryView()
/* 10:   */     {
/* 11:   */       public K getKey()
/* 12:   */       {
/* 13:15 */         return Helper.this.getKey();
/* 14:   */       }
/* 15:   */       
/* 16:   */       public T getValue()
/* 17:   */       {
/* 18:16 */         return Helper.this.getValue();
/* 19:   */       }
/* 20:   */     };
/* 21:   */   }
/* 22:   */ }


/* Location:           D:\CODinsa\Partage\public-2014\proxy.jar
 * Qualified Name:     common.Helper
 * JD-Core Version:    0.7.0.1
 */