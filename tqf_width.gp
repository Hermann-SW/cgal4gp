read("cgal4.gp");

assert(b,s)=if(!(b), error(Str(s)));

dbg(a,b,c="")=if(getenv("dbg"),print(a,b,c));

SquaresRepresentations3(n)={
  my(R=List(),m=sqrtint(n));
  for(a=-m,m,
    for(b=-m,m,
      for(c=-m,m,
        if(a^2+b^2+c^2==n,
          listput(R,[a,b,c])
        )
      )
    )
  );
  Vec(R);
}

get_tqf(n,vstart)={
    assert(n%4!=0);
    assert(n%8!=7);
    my(Q,v,b,p,a12);
    if(n%4==2,
        for(vv=vstart,oo,
            if(ispseudoprime((4*vv+1)*n-1),
                v=vv; break()));
        write("/dev/stderr","next vstart: ",v+1);
        b=4*v+1;
        p=b*n-1;
        assert(kronecker(-b,p)==1);
        a12=lift(sqrt(Mod(-b,p)));
        ,
        my(c=4-(n%4));
        assert(((c*n-1)/2)%2==1);
        for(vv=vstart,oo,
            if(ispseudoprime(((8*vv+c)*n-1)/2),
                v=vv; break()));
        write("/dev/stderr","next vstart: ",v+1);
        b=8*v+c;
        p=(b*n-1)/2;
        assert(kronecker(-b,p)==1);
        my(r0=lift(sqrt(Mod(-b,p))));
        a12=abs(r0-(1-(r0%2))*p));
    [(b+a12^2)/(b*n-1),a12,1;a12,b*n-1,0;1,0,n];
}

{
    if(getenv("p")!=0&&getenv("q")!=0,
        p=eval(getenv("p"));
        q=eval(getenv("q"));
        assert(p%4==1&&q%4==1&&isprime(p)&&isprime(q));
        n=p*q;
        S=SquaresRepresentations3(n);
        assert(p==q||12*qfbclassno(-4*n)==#S);
        print("n=",n);

        if(getenv("vstart"),
            my(Q,G,x=[0,0,1]~);
            vstart=eval(getenv("vstart"));

            Q=get_tqf(n,vstart);
            assert(type(Q)=="t_MAT");
            assert(qfeval(Q,x)==n);
            assert(matdet(Q)==1);

            dbg(" Q=",Q);
            G=qflllgram(Q,1);
            dbg(" G=",G);
            dbg(" G^-1=",G^-1);
            assert(G~*Q*G==matdiagonal([1,1,1]));
            assert(norml2(G^-1*x)==n);

            S=[G*y~|y<-S]);

        print("#S=",#S);
        CGAL_Width(S);
        CGAL_get_squared_width(num,denom);
        print("squared width: ",num/denom," [",num,"/",denom,"]");
        print("build direction: ",CGAL_get_build_direction());
        print("optimal solutions: ",CGAL_get_number_of_optimal_solutions());
        CGAL_get_all_build_directions(dir);
        print("workaround(all build directions): ", Set([d/gcd(d)*if(d[1]<0,-1,1) | d<-dir]));
    )
}
