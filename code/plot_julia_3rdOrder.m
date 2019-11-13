raw_t = load('temp/times_raw.txt');
raw_a = load('temp/a_raw.txt');
raw_v = load('temp/v_raw.txt');
raw_x = load('temp/x_raw.txt');


fine_t = load('temp/times_fine.txt');
fine_a = load('temp/a_fine.txt');
fine_v = load('temp/v_fine.txt');
fine_x = load('temp/x_fine.txt');

% plot t vs a for each dimension
figure(1)
plot(fine_t, fine_a)
hold on
    plot(raw_t(1:end-1), raw_a, 'o')
hold off

% plot t vs v for each dimension
figure(2)
plot(fine_t, fine_v)
hold on
    plot(raw_t, raw_v, 'o')
hold off

% plot t vs x for each dimension
figure(3)
plot(fine_t, fine_x)
hold on
    plot(raw_t, raw_x, 'o')
hold off

% now plot 3d plot of change in distance
figure(4)
plot3(fine_x(:,1), fine_x(:,2), fine_x(:,3))


