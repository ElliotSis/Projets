/*  1:   */ package common;
/*  2:   */ 
/*  3:   */ public class Pair<T>
/*  4:   */   extends Couple<T, T>
/*  5:   */ {
/*  6:   */   public Pair(T first, T second)
/*  7:   */   {
/*  8: 9 */     super(first, second);
/*  9:   */   }
/* 10:   */   
/* 11:   */   public Pair(Couple<T, T>.View src)
/* 12:   */   {
/* 13:13 */     super(src.first(), src.second());
/* 14:   */   }
/* 15:   */ }


/* Location:           D:\CODinsa\Partage\public-2014\proxy.jar
 * Qualified Name:     common.Pair
 * JD-Core Version:    0.7.0.1
 */