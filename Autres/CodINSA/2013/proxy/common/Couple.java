/*  1:   */ package common;
/*  2:   */ 
/*  3:   */ public class Couple<A, B>
/*  4:   */   implements ShallowViewable<View>
/*  5:   */ {
/*  6:   */   public A first;
/*  7:   */   public B second;
/*  8:   */   
/*  9:   */   public Couple(A first, B second)
/* 10:   */   {
/* 11:12 */     this.first = first;
/* 12:13 */     this.second = second;
/* 13:   */   }
/* 14:   */   
/* 15:   */   public Couple(Couple<A, B>.View src)
/* 16:   */   {
/* 17:17 */     this.first = src.first();
/* 18:18 */     this.second = src.second();
/* 19:   */   }
/* 20:   */   
/* 21:   */   public class View
/* 22:   */     implements ShallowViewable.ShallowView
/* 23:   */   {
/* 24:   */     public View() {}
/* 25:   */     
/* 26:   */     public A first()
/* 27:   */     {
/* 28:22 */       return Couple.this.first;
/* 29:   */     }
/* 30:   */     
/* 31:   */     public B second()
/* 32:   */     {
/* 33:23 */       return Couple.this.second;
/* 34:   */     }
/* 35:   */   }
/* 36:   */   
/* 37:   */   public Couple<A, B>.View shallowView()
/* 38:   */   {
/* 39:28 */     return new View();
/* 40:   */   }
/* 41:   */   
/* 42:   */   public static <A extends Viewable<AV>, AV extends Viewable.View, B extends Viewable<BV>, BV extends Viewable.View> Couple<AV, BV>.View view(Couple<A, B> src)
/* 43:   */   {
/* 44:35 */     return new Couple(((Viewable)src.first).view(), ((Viewable)src.second).view()).shallowView();
/* 45:   */   }
/* 46:   */   
/* 47:   */   public int hashCode()
/* 48:   */   {
/* 49:41 */     int hashFirst = this.first != null ? this.first.hashCode() : 0;
/* 50:42 */     int hashSecond = this.second != null ? this.second.hashCode() : 0;
/* 51:   */     
/* 52:44 */     return (hashFirst + hashSecond) * hashSecond + hashFirst;
/* 53:   */   }
/* 54:   */   
/* 55:   */   public boolean equals(Object other)
/* 56:   */   {
/* 57:48 */     if ((other instanceof Couple))
/* 58:   */     {
/* 59:49 */       Couple otherCouple = (Couple)other;
/* 60:50 */       return 
/* 61:51 */         ((this.first == otherCouple.first) || (
/* 62:52 */         (this.first != null) && (otherCouple.first != null) && 
/* 63:53 */         (this.first.equals(otherCouple.first)))) && (
/* 64:54 */         (this.second == otherCouple.second) || (
/* 65:55 */         (this.second != null) && (otherCouple.second != null) && 
/* 66:56 */         (this.second.equals(otherCouple.second))));
/* 67:   */     }
/* 68:59 */     return false;
/* 69:   */   }
/* 70:   */   
/* 71:   */   public String toString()
/* 72:   */   {
/* 73:64 */     return "(" + this.first + ", " + this.second + ")";
/* 74:   */   }
/* 75:   */ }


/* Location:           D:\CODinsa\Partage\public-2014\proxy.jar
 * Qualified Name:     common.Couple
 * JD-Core Version:    0.7.0.1
 */