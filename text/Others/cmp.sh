while true; do
    ./maker > input
    ./Correct < input > Correct.out
    ./Wrong < input > Wrong.out
    if diff Correct.out Wrong.out; then
        printf "AC\n";
    else
        printf "WA\n";
        exit 0;
    fi
done

849-857,886-891,1048-1067,1178-1185,1225-1247,1251-1273,2021-2029,2233-2244,2333-2339,2279-2282,7-12