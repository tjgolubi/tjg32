/^Compiled with/ {
  optimize = $3;
}

/^Crc[0-9]::Update time:/ {
  num = $1;
  dt = $3;
  name = $7;
  names[num] = name;
  table[num][optimize] = dt;
}

END {
  PROCINFO["sorted_in"] = "@ind_str_asc";
  for (num in table) {
    printf "| %-14s", "Algorithm";
    for (opt in table[num])
      printf " |  %3s  ", opt;
    printf " |\n|:---------------";
    for (opt in table[num])
      printf "|-------:";
    printf "|\n";
    break;
  }

  for (num in table) {
    printf "| %-14s", names[num];
    for (opt in table[num])
      printf " |%7s", table[num][opt];
    printf " |\n";
  }
}
